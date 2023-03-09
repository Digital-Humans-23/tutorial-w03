//
// Created by Dongho Kang on 06.09.22.
//

#include <pycrl/pycrl.h>
#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include <pycrlbase/Viewer.h>

namespace py = pybind11;

namespace pycrl {

PYBIND11_MODULE(pycrl, m) {  //Defining module
    m.doc() = "Python binding of locomotion simulator.";

    py::class_<Viewer>(m, "Viewer")
        .def(py::init())
        .def(py::init<int, int>())
        .def_readonly("width", &Viewer::width)
        .def_readonly("height", &Viewer::height)
        .def_readwrite("show_plots", &Viewer::showPlots)
        .def("render", &Viewer::render)
        .def("read_pixels",
             [](Viewer &self, py::array_t<unsigned char> rgb) {
                 py::buffer_info info = rgb.request();
                 self.readPixels(static_cast<unsigned char *>(info.ptr));
             })
        .def("close", &Viewer::close)
        .def("__repr__", [](const Viewer &) { return "<pyloco Viewer>"; });
}

}  // namespace pycrl
