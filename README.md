<div align="center">

<img src="https://res.cloudinary.com/dbmcddwjd/image/upload/v1783410838/file_00000000a2b471fba91bcdf2f3a398fb_t6gln5.png" alt="py_tokenizer logo" width="140" height="140" style="border-radius: 50%; object-fit: cover;" />

# py_tokenizer

### A high-performance C++ powered BPE tokenizer for Python, with a built-in engine for learning how tokenization actually works.

[![Python](https://img.shields.io/badge/python-3.8%2B-blue?style=flat-square&logo=python&logoColor=white)](https://www.python.org/)
[![C++](https://img.shields.io/badge/core-Modern%20C%2B%2B-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/license-MIT-green?style=flat-square)](#license)
[![PyPI](https://img.shields.io/badge/pypi-py__tokenizer__ansh-blue?style=flat-square&logo=pypi&logoColor=white)](https://pypi.org/project/py_tokenizer_ansh/)
[![Performance](https://img.shields.io/badge/performance-optimized-orange?style=flat-square)](#performance)
[![Multithreaded](https://img.shields.io/badge/multithreading-enabled-purple?style=flat-square)](#architecture)

</div>

---

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Quick Start](#quick-start)
  - [1. Production Tokenizer — `engine`](#1-production-tokenizer--engine)
  - [2. Learning Tokenizer — `basic_engine`](#2-learning-tokenizer--basic_engine)
- [Architecture](#architecture)
- [Why py_tokenizer?](#why-py_tokenizer)
- [Performance](#performance)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Author](#author)

---

## Introduction

**py_tokenizer** is a Python package with a Modern C++ core, built to tokenize text using Byte Pair Encoding (BPE) — the same family of algorithm behind many production-grade language model tokenizers.

Most tokenizer implementations you find while learning NLP fall into one of two camps: they are either too simplistic to be used on real data, or too abstracted to actually teach you what is happening under the hood. py_tokenizer was built to close that gap by shipping **two dedicated engines** instead of one compromise:

- A **production engine**, written in C++ and exposed to Python through native bindings, designed to tokenize large text files quickly using multithreading.
- A **learning engine**, written for clarity rather than speed, that prints every split and every merge step directly to your terminal so you can *see* BPE happen.

The goal is simple: give developers a tokenizer fast enough for real datasets, and give students and researchers a tokenizer transparent enough to actually learn from.

---

## Features

- **Modern C++ core** — the production tokenizer is implemented in Modern C++ for speed, safety, and efficient memory management.
- **Native Python bindings** — call high-performance C++ code directly from Python with a simple function call.
- **Multithreaded processing** — large files are processed using multiple threads to significantly reduce tokenization time.
- **Large file support** — designed from the ground up to handle real-world, large-scale text datasets rather than toy examples.
- **Automatic vocabulary generation** — produces a reusable `vocabulary.json` you can load into downstream NLP pipelines.
- **File metadata export** — produces `file_info.json` describing the processed dataset.
- **Dedicated educational engine** — `basic_engine` is purpose-built for learning and demonstrating BPE, independent of the production pipeline.
- **Clean, minimal API** — both engines are exposed through simple, explicit function calls with no hidden configuration.
- **Beginner friendly** — clear parameters, predictable output, and readable terminal logs for the learning engine.
- **High performance by design** — the production engine is architected for speed and scalability on real datasets.

---

## Installation

py_tokenizer is available on PyPI:

```bash
pip install py_tokenizer_ansh==0.0.4
```

Requires Python 3.8 or newer. No manual C++ compilation is required — the native extension ships prebuilt with the package.

---

## Quick Start

### 1. Production Tokenizer — `engine`

The production tokenizer is the main, high-performance tokenizer in this package. It is written in C++ and designed to process large text files efficiently using multithreading.

```python
import py_tokenizer

engine = py_tokenizer.engine(
    file_path="/storage/emulated/0/data.txt",
    chunk_size=4,
    get_file_info=True,
    normalize=False,
    epoch=100,
    cpu_count=8,
    use_thread=True
)
```

**Parameters explained**

| Position | Parameter | Description |
|---|---|---|
| 1 | `file_path` | Path to the input text file to be tokenized. Can point to very large datasets. |
| 2 | `min_frequency` | Minimum frequency a token pair must reach before it is merged during BPE training. |
| 3 | `normalize` | Whether to normalize the input text (e.g. casing/whitespace handling) before tokenization. |
| 4 | `lowercase` | Whether to lowercase the input text before processing. |
| 5 | `vocab_size` | Target vocabulary size — the number of merge operations / vocabulary entries to generate. |
| 6 | `num_threads` | Number of threads used to parallelize tokenization across the input file. |
| 7 | `save_output` | Whether to write the resulting vocabulary and file metadata to disk. |

**Generated files**

Running `engine(...)` produces two files in your working directory:

- **`vocabulary.json`** — the learned BPE vocabulary, containing the merged tokens generated from your dataset. This file is reusable and can be loaded by downstream NLP pipelines that need a trained vocabulary.
- **`file_info.json`** — metadata about the processed input file, such as file size and processing details, useful for logging, debugging, and reproducibility.

This engine is intended for **serious workloads**: production pipelines, large corpora, and real datasets where performance and memory efficiency matter.

---

### 2. Learning Tokenizer — `basic_engine`

The learning tokenizer is intentionally simple. It exists to help you understand *how* BPE actually works — one split, one merge, at a time — by printing every step to your terminal.

```python
from py_tokenizer import basic_engine

sentence = "hii this is an test sentance"

basic_engine(
    sentence,
    normalize=False,
    epoch=20
)
```

**Parameters explained**

| Parameter | Description |
|---|---|
| `sentence` | The input text (a single string) you want to tokenize and observe. |
| `normalize` | Whether to normalize the text before running BPE (e.g. casing/whitespace). |
| `epoch` | The number of BPE merge iterations to run — each epoch performs one merge step. |

**Output**

`basic_engine` does not write any files. Instead, it prints directly to the terminal:

- The initial **split tokens** (the sentence broken into its starting units).
- Each **merged token** produced at every epoch, so you can watch the vocabulary evolve step by step.

This engine is **not** intended for large datasets. It exists purely for:

- learning BPE
- understanding token merging
- practicing tokenizer concepts
- education
- experimenting

It will continue to receive educational improvements and new learning-focused features over time, independent of the production engine.

---

## Architecture

py_tokenizer follows a straightforward pipeline from raw text to a usable vocabulary:

```
                 ┌────────────────────┐
                 │      Raw Text       │
                 │ (single file or     │
                 │  large dataset)     │
                 └─────────┬───────────┘
                           │
                           ▼
                 ┌────────────────────┐
                 │       Split         │
                 │  Break text into    │
                 │  base-level units   │
                 └─────────┬───────────┘
                           │
                           ▼
                 ┌────────────────────┐
                 │      BPE Merge      │
                 │  Repeatedly merge   │
                 │  the most frequent  │
                 │  adjacent pairs     │
                 └─────────┬───────────┘
                           │
                           ▼
                 ┌────────────────────┐
                 │     Vocabulary      │
                 │  Final set of       │
                 │  learned tokens     │
                 └─────────┬───────────┘
                           │
                           ▼
                 ┌────────────────────┐
                 │     JSON Export     │
                 │ vocabulary.json     │
                 │ file_info.json      │
                 └────────────────────┘
```

The **production engine** runs this pipeline in C++, distributing the split and merge stages across multiple threads to process large files efficiently before exporting the final vocabulary and metadata to JSON.

The **learning engine** runs the same conceptual pipeline — split, then merge — but does so step by step in Python-visible output, without threading or file export, so every stage is observable.

---

## Why py_tokenizer?

A plain, single-threaded tokenizer works fine for small examples, but real datasets change the equation entirely. Reading, splitting, and merging tokens across millions of lines of text is computationally expensive, and doing it sequentially wastes available CPU resources.

**Why multithreading matters**

The production engine distributes tokenization work across multiple threads so that large files are processed using the hardware you already have, instead of leaving cores idle. This is the difference between a tokenizer that works on toy examples and one that is realistically usable on production-scale datasets.

**Why two engines instead of one**

Most tokenizer libraries force a tradeoff: either you get a fast black-box implementation you can't easily learn from, or a readable implementation that can't handle real data. py_tokenizer avoids that tradeoff by keeping the two goals separate:

- `engine` — optimized purely for performance, scale, and reusable output.
- `basic_engine` — optimized purely for clarity, step-by-step visibility, and learning.

You get the right tool for the job, whether that job is training a vocabulary on a large corpus or teaching yourself how BPE merges actually happen.

---

## Performance

The production engine is architected around multithreading, efficient memory usage, and a Modern C++ core specifically to handle large text files at scale.

Formal benchmark numbers are not yet published. Rather than publishing estimated or unverified figures, this README intentionally omits performance claims until reproducible benchmarks are available. **Benchmarks will be added in a future release**, along with details on methodology and hardware used, so results can be independently verified.

---

## Roadmap

py_tokenizer is under active development. Planned improvements include:

- Better text normalization options
- Improved Unicode and multilingual support
- Additional BPE features and configuration options
- Better visualization tools for the learning engine
- Research into GPU-accelerated tokenization
- Support for more vocabulary export formats
- Expanded and more detailed documentation

---

## Contributing

Contributions, issues, and feature requests are welcome. Whether it's improving performance, extending the learning engine, fixing bugs, or improving documentation, all contributions help make py_tokenizer better for everyone.

To contribute:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Open a pull request with a clear description of what you changed and why

If you're new to the project, feel free to open an issue first to discuss the change you'd like to make.

---

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## Author

Created with ❤️ by **Ansh Raj**

