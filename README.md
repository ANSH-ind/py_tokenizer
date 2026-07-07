<div align="center">
<img src="https://res.cloudinary.com/dbmcddwjd/image/upload/v1783410838/file_00000000a2b471fba91bcdf2f3a398fb_t6gln5.png" alt="py_tokenizer Logo" width="250"/>
<h1>py_tokenizer</h1>
<p><b>High-Performance, Multithreaded Byte-Pair Encoding (BPE) Tokenizer</b></p>
<a href="https://pypi.org/project/py_tokenizer_ansh/"><img src="https://img.shields.io/pypi/v/py_tokenizer_ansh.svg?style=for-the-badge&color=0073B7" alt="PyPI version" /></a>
<a href="https://www.python.org/downloads/"><img src="https://img.shields.io/badge/Python-3.8+-blue.svg?style=for-the-badge&logo=python&logoColor=white" alt="Python Version" /></a>
<a href="#"><img src="https://img.shields.io/badge/C++-17-00599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++17" /></a>
<a href="#"><img src="https://img.shields.io/badge/Performance-Highly%20Optimized-success.svg?style=for-the-badge" alt="Performance" /></a>
<a href="#"><img src="https://img.shields.io/badge/Multithreading-Enabled-orange.svg?style=for-the-badge" alt="Multithreading" /></a>
<a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License: MIT" /></a>
<br />
<br />
</div>
## Introduction
Welcome to **py_tokenizer**.
Natural Language Processing demands efficient preprocessing. When dealing with terabytes of text, traditional single-threaded tokenizers become severe bottlenecks. This package is designed to bridge the gap between heavy-duty production requirements and educational clarity.
Written in Modern C++ and bound to Python, this package delivers extremely fast, memory-efficient tokenization tailored for large-scale real-world datasets, while simultaneously offering a secondary engine for learning and visualizing the intricacies of Byte-Pair Encoding (BPE).
## Features
 * **Modern C++ Core**: Built on a high-performance C++ backend ensuring minimal memory overhead and maximum throughput.
 * **Python API**: Seamless, native-feeling Python bindings for effortless integration into existing Machine Learning pipelines.
 * **Multithreaded Processing**: Leverages concurrent CPU threads to tokenize massive text documents exponentially faster than standard sequential algorithms.
 * **Large File Support**: Safely processes files exceeding system RAM via chunked streaming and intelligent memory management.
 * **Dual-Engine Architecture**: Features a robust engine for production workloads and a basic_engine for educational and experimental purposes.
 * **Artifact Generation**: Automatically exports deterministic, highly reusable vocabulary.json and file_info.json artifacts.
 * **Clean API Design**: Strictly typed, beginner-friendly API surface that hides internal complexity without sacrificing power.
## Installation
The package is officially hosted on PyPI. Install the specific stable release using pip:
```bash
pip install py_tokenizer_ansh==0.0.4
```
*Note: Pre-compiled wheels are provided for major operating systems. Ensure you have a C++17 compatible compiler if building from source.*
## Quick Start
The library exports two primary APIs, each serving a distinct purpose in the NLP development lifecycle.
### 1. The Production Tokenizer (engine)
The engine function is the powerhouse of the library. It is strictly built for serious workloads, NLP preprocessing, and handling extremely large datasets.
```python
from py_tokenizer import engine
# Initialize the production tokenization pipeline
engine(
    "/storage/emulated/0/Download/big.txt/big.txt",  # 1. Target File
    4,                                               # 2. Threads
    True,                                            # 3. Normalize
    False,                                           # 4. Strict Mode
    100,                                             # 5. Target Vocab Size
    8,                                               # 6. Chunk/Batch Size
    True                                             # 7. Export Metadata
)
```
#### Parameter Breakdown

| Position | Parameter | Type | Description |
| :--- | :--- | :--- | :--- |
| **1** | file_path | str | Absolute path to the raw text document to be processed. |
| **2** | threads | int | Number of concurrent threads to spawn for the splitting and merging phases. |
| **3** | normalize | bool | Whether to apply standard text normalization (whitespace stripping, NFKC). |
| **4** | strict_mode | bool | Toggles strict character fallback. If False, unknown bytes are gracefully handled. |
| **5** | vocab_size | int | The desired final vocabulary size after BPE merging. |
| **6** | batch_size | int | Memory allocation chunking size. Prevents Out-Of-Memory (OOM) errors on large files. |
| **7** | export_meta | bool | Instructs the engine to generate detailed execution metrics. |

#### Generated Output
Upon successful execution, the engine writes two files directly to disk:
 1. **vocabulary.json**: The final computed BPE vocabulary mapping (tokens to IDs). Ready to be loaded into your PyTorch or TensorFlow embedding layers.
 2. **file_info.json**: A comprehensive metadata diagnostic file detailing execution time, thread utilization, token frequencies, and compression ratios.
### 2. The Learning Tokenizer (basic_engine)
The basic_engine is intentionally stripped down. It does not handle large files, nor does it spawn background threads. Its sole purpose is education: visualizing how BPE token merging works in real-time.
```python
from py_tokenizer import basic_engine
sentence = "hii this is an test sentance"
# Run the educational BPE engine
basic_engine(
    sentence,
    normalize=False,
    epoch=20
)
```
#### Parameter Breakdown

| Parameter | Type | Description |
| :--- | :--- | :--- |
| sentence | str | A short string/sentence to tokenize and visualize. |
| normalize | bool | Whether to apply basic text cleaning before visualization. |
| epoch | int | The number of BPE merge iterations to perform and print to the terminal. | <br> **Terminal Output:** <br> This function prints directly to stdout, displaying the text split into base characters, followed by a step-by-step visualization of the most frequent pairs merging over the specified epoch count. <br> ## Architecture <br> The internal pipeline is highly optimized, moving data sequentially through multithreaded workers before compiling the final JSON artifacts. <br> ```text <br> +----------------------+       +-----------------------+       +-----------------------+
| Raw Text Document | --> | Multithreaded Split | --> | Parallel BPE |
| (Disk Streaming) |  | (Worker Pool) |  | Frequency Count | <br> +----------------------+       +-----------------------+       +-----------------------+
| <br> v <br> +----------------------+       +-----------------------+       +-----------------------+
| JSON Serialization | <-- | Vocabulary Builder | <-- | Iterative Merge |
| (Disk I/O) |  | (ID Assignment) |  | (Target Vocab Size) | <br> +----------------------+       +-----------------------+       +-----------------------+
| <br> v <br> +----------------------+
| vocabulary.json |
| file_info.json |

+----------------------+
```
## Why py_tokenizer?
### The Multithreading Advantage
Standard tokenizers written purely in Python suffer from the Global Interpreter Lock (GIL), forcing them to process text sequentially. py_tokenizer drops down into C++ to bypass the GIL, distributing chunks of your dataset across all available CPU cores. This results in near-linear scaling; a 16-core machine will process your dataset almost 16 times faster.
### The Two-Engine Philosophy
Most libraries force you to choose between learning and deployment. Production tokenizers are too complex and obfuscated to learn from, while educational scripts crash when handed a 50GB corpus. We built two distinct APIs under one roof: use basic_engine to understand the math, and engine to process your production data.
## Performance
The production engine is strictly architected for speed and horizontal scalability on modern multi-core processors. Memory mapping and aggressive C++ string manipulation ensure that RAM usage remains flat regardless of dataset size.
Extensive, standardized benchmarks against other industry tokenizers are currently being compiled and will be published in upcoming releases.
## Roadmap
We are actively developing py_tokenizer. Our immediate focus areas include:
 * [ ] **Advanced Normalization**: Implementing robust, locale-aware Unicode normalization algorithms.
 * [ ] **Expanded BPE Features**: Support for byte-fallback, regex pre-tokenization, and custom merge rules.
 * [ ] **Visualization Suite**: Exporting HTML/CSS based tokenization visualizations for the basic_engine.
 * [ ] **Export Formats**: Adding support for Hugging Face tokenizer.json format compatibility.
 * [ ] **Hardware Acceleration**: Researching GPU/CUDA based parallel BPE compilation.
 * [ ] **Comprehensive Documentation**: Launching a dedicated documentation site with tutorials and benchmark data.
## Contributing
We welcome contributions from the open-source NLP and C++ communities. Whether it is a bug report, a performance optimization, or a new feature request, your input is highly valued.
Please ensure that pull requests targeting the C++ backend maintain strict memory safety and do not introduce data races into the multithreaded pipeline.
## License
This project is licensed under the **MIT License**. You are free to use, modify, and distribute this software in both open-source and commercial projects.
<div align="center">
<p>Created with love by <b>Ansh Raj</b></p>
<p>Maintainer and Technical Writer</p>
</div>
