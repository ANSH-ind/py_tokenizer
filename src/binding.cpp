#include "engine/engine.h"
#include "engine/basic_engine.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <thread>

inline const size_t c = std::thread::hardware_concurrency();

namespace py = pybind11;

PYBIND11_MODULE(py_tokenizer, tokenizer){
    py::class_<engine>(tokenizer, "engine")
        .def(
            py::init<std::string, int, bool, bool, int, int, bool>(),
            py::arg("file_path"),
            py::arg("chunk_size") = 1,
            py::arg("get_file_info") = false,
            py::arg("normalize") = false,
            py::arg("epoch") = 20,
            py::arg("cpu_count") = c,
            py::arg("use_thread") = true
        );
    py::class_<basic_engine>(tokenizer, "basic_engine")
        .def(
            py::init<std::string, bool, int>(),
            py::arg("sentance"),
            py::arg("normalize") = false,
            py::arg("epoch") = 10
        );
}
