<div align="center">
<img src="https://res.cloudinary.com/dbmcddwjd/image/upload/v1783410838/file_00000000a2b471fba91bcdf2f3a398fb_t6gln5.png" alt="py_tokenizer Logo" width="250"/>
# py_tokenizer
**A High-Performance Byte Pair Encoding (BPE) Tokenizer for Modern AI Workflows.**
Version
Language
Python
Build
Platform
License
</div>
## Introduction
py_tokenizer is a high-performance Byte Pair Encoding (BPE) tokenizer engineered entirely in modern C++17. It provides seamless Python bindings via pybind11, bridging the gap between low-level performance and high-level scripting convenience. Designed to be fast, memory-efficient, and highly modular, py_tokenizer is built to integrate effortlessly into advanced Artificial Intelligence and Machine Learning pipelines, specifically catering to Large Language Models (LLMs).
## Key Features

| Feature | Description |
| :--- | :--- |
| **High Performance** | Optimized core written in C++17 for maximum throughput and minimal latency. |
| **Multi-threading** | Built-in support for concurrent processing to handle massive text corpora rapidly. |
| **Memory Efficient** | Strict resource management ensures low memory overhead during training and encoding. |
| **Python Integration** | Native Python bindings utilizing pybind11 for seamless ML framework integration. |
| **Modular Architecture** | Clean separation of concerns allows for easy extension and customization of tokenization rules. |
| **AI/LLM Ready** | Designed specifically for the stringent requirements of modern transformer architectures. |

## Why py_tokenizer?
Tokenization is the critical first step in natural language processing. While many tokenizers exist, py_tokenizer differentiates itself by focusing on raw compute efficiency without sacrificing usability. It is developed natively on mobile/embedded environments (Android via Termux), which enforces strict memory constraints and results in a highly optimized, lean codebase. Whether you are deploying on resource-constrained devices or scaling up on Linux servers, py_tokenizer delivers consistent, robust performance.
## Project Architecture
The project follows a standard wrapper architecture:
 1. **Core Library (C++)**: Handles all intensive computations, string manipulations, frequency counting, and merging operations.
 2. **Binding Layer (pybind11)**: Exposes the C++ classes and methods to Python, handling memory safety and type conversions natively.
 3. **Python API**: Provides a Pythonic interface, allowing users to import the tokenizer just like any native Python module.
## Installation & Building from Source
Currently, py_tokenizer supports Linux and Android (via Termux). Windows and macOS support are planned for future releases.
### Prerequisites
 * CMake (Version 3.10 or higher)
 * C++ Compiler (GCC or Clang supporting C++17)
 * Python 3.x
 * pybind11 headers
### Build Instructions
 1. Clone the repository:
```bash
git clone [https://github.com/ANSH-ins/py_tokenizer.git](https://github.com/ANSH-ins/py_tokenizer.git)
cd py_tokenizer
```
 2. Create a build directory and compile:
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```
 3. Install the Python module:
```bash
python setup.py install
```
## Usage Examples
### Python Integration
```python
import py_tokenizer
# Initialize the BPE Tokenizer
tokenizer = py_tokenizer.BPETokenizer()
# Train the tokenizer on your dataset
tokenizer.train(
    file_path="dataset.txt", 
    vocab_size=10000, 
    special_tokens=["<PAD>", "<UNK>", "<BOS>", "<EOS>"]
)
# Encode text to tokens
text = "Artificial intelligence relies on efficient tokenization."
encoded_ids = tokenizer.encode(text)
print("Encoded IDs:", encoded_ids)
# Decode tokens back to text
decoded_text = tokenizer.decode(encoded_ids)
print("Decoded Text:", decoded_text)
```
### C++ Integration
```cpp
#include "py_tokenizer/bpe_tokenizer.hpp"
#include <iostream>
#include <vector>
#include <string>
int main() {
    // Initialize
    py_tokenizer::BPETokenizer tokenizer;
    // Train
    std::vector<std::string> special_tokens = {"<PAD>", "<UNK>", "<BOS>", "<EOS>"};
    tokenizer.train("dataset.txt", 10000, special_tokens);
    // Encode
    std::string text = "Artificial intelligence relies on efficient tokenization.";
    std::vector<int> encoded_ids = tokenizer.encode(text);
    // Decode
    std::string decoded_text = tokenizer.decode(encoded_ids);
    std::cout << "Decoded: " << decoded_text << std::endl;
    return 0;
}
```
## Constructor Arguments
When initializing or training the BPETokenizer, you can configure its behavior using the following parameters:

| Argument | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| vocab_size | int | Required | The target size of the vocabulary to be generated. |
| file_path | string | Required | Path to the text corpus for training the BPE model. |
| special_tokens | list / vector | [] | List of special structural tokens (e.g., <UNK>). |
| num_threads | int | 1 | Number of threads to utilize during the training phase. |
| casing | enum | PRESERVE | Rules for handling text capitalization (LOWERCASE, PRESERVE). |

<details>
<summary><b>View Project Folder Structure</b> (Click to Expand)</summary>
```text
py_tokenizer/
├── CMakeLists.txt         # Build configuration
├── README.md              # Project documentation
├── setup.py               # Python installation script
├── include/               # C++ Header files
│   └── py_tokenizer/
│       ├── bpe_tokenizer.hpp
│       └── utils.hpp
├── src/                   # C++ Source files
│   ├── bpe_tokenizer.cpp
│   └── utils.cpp
├── bindings/              # pybind11 wrapper code
│   └── bindings.cpp
├── tests/                 # Unit tests (C++ and Python)
│   ├── test_core.cpp
│   └── test_tokenizer.py
└── examples/              # Usage examples
    ├── example.cpp
    └── example.py
```
</details>
<details>
<summary><b>Roadmap & Future Plans</b> (Click to Expand)</summary>
 * **Version 0.03**: Introduce streaming text tokenization for continuous data feeds.
 * **Platform Expansion**: Official build support and CI/CD pipelines for Windows and macOS.
 * **Advanced Normalization**: Implement customizable pre-tokenization steps (Unicode normalization, regex splitting).
 * **GPU Acceleration**: Research feasibility of offloading frequency counts to CUDA/OpenCL.
 * **Hugging Face Hub**: Native export formats to integrate directly with the transformers library.
</details>
## Performance Goals
 1. **Zero-Copy Serialization**: Minimizing memory duplication when passing standard library containers between C++ and Python.
 2. **Cache Locality**: Utilizing contiguous memory structures in C++ to improve CPU cache hit rates during byte-pair merges.
 3. **Scalability**: Ensuring the training complexity remains sub-quadratic relative to the vocabulary size.
## Documentation & Website
 * **Official Documentation**: py_tokenizer Docs
 * **Developer Portfolio**: Ansh Studios
## Developer Information

| Detail | Information |
| :--- | :--- |
| **Developer Name** | Ansh Raj |
| **Location** | India |
| **Education** | Class 9th |
| **Core Competency** | C++ |
| **Languages** | C++, Python, JavaScript, HTML, CSS, Kotlin, Go |
| **Environments** | Termux, Cxxdroid, Pydroid, Acode |

## Contact & Links
 * **Email**: anshraj0000000001@gmail.com
 * **GitHub**: ANSH-ins
## Contributing
Contributions to py_tokenizer are highly encouraged. Please follow standard open-source workflows: fork the repository, create a feature branch, commit your changes with clear messages, and open a Pull Request. Ensure that all tests pass and that your code adheres to modern C++ conventions.
## Acknowledgements
Special thanks to the open-source community, the maintainers of pybind11, and the developers behind Android coding environments like Termux and Cxxdroid that made the development of this project possible on mobile devices.
## License
This project is licensed under the **MIT License**. See the LICENSE file in the repository for full details. You are free to use, modify, and distribute this software in both open-source and commercial projects.
