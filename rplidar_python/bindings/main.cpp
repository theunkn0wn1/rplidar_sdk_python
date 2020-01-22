
#include "main.h"
#include <iostream>
#include <rplidar.h>
#include <rplidar_driver.h>

class Lidar {
private:
  rp::standalone::rplidar::RPlidarDriver *_driver = nullptr;

public:
  ~Lidar() {
    if (this->_driver == nullptr) {
      return; // nothing to be done
    }
    rp::standalone::rplidar::RPlidarDriver::DisposeDriver(this->_driver);
    this->_driver = nullptr;
  }
  Lidar() {
    this->_driver = rp::standalone::rplidar::RPlidarDriver::CreateDriver();
  }
  bool is_connected() {
    if (this->_driver == nullptr) {
      return false;
    }
    return this->_driver->isConnected();
  }
  uint32_t start_motor() {
    this->assert_driver();
    return this->_driver->startMotor();
  }
  uint32_t stop_motor() {
    this->assert_driver();

    return this->_driver->stopMotor();
  }
  void assert_driver() const {
    if (_driver == nullptr) {
      throw std::runtime_error("_driver was nullptr");
    }
  }

  uint32_t connect(const std::string &port, uint32_t baud, uint32_t flags = 0) {
    this->assert_driver();
    return this->_driver->connect(port.c_str(), baud, flags);
  }

  void disconnect() {
    this->assert_driver();
    this->_driver->disconnect();
  }

  pybind11::tuple get_device_info() {
    this->assert_driver();
    uint32_t result;
    rplidar_response_device_info_t info = {};
    result = this->_driver->getDeviceInfo(info);
    return py::make_tuple(result, info);
  }

  std::vector<pybind11::tuple> read()
  {
    this->assert_driver();

    std::vector<pybind11::tuple> points[1024];
    this->_driver->startScan(false, true);
  }
};

PYBIND11_MODULE(rplidar_sdk, module) {
  module.doc() = "module docstring is modular";
  module.def("add", &add, "function for adding two integers");
  py::class_<Lidar>(module, "LidarDriver")
      .def(py::init())
      .def("is_connnected", &Lidar::is_connected)
      .def("start_motor", &Lidar::start_motor)
      .def("stop_motor", &Lidar::stop_motor)
      .def("connect", &Lidar::connect)
      .def("disconnect", &Lidar::disconnect)
      .def("get_device_info", &Lidar::get_device_info);
  py::class_<rplidar_response_device_info_t>(module, "DeviceInfo")
      .def_readonly("model", &rplidar_response_device_info_t::model)
      .def_readonly("firmware_version",
                    &rplidar_response_device_info_t::firmware_version)
      .def_readonly("hardware_version",
                    &rplidar_response_device_info_t::hardware_version)
      .def_readonly("serialnum", &rplidar_response_device_info_t::serialnum)

      ;
}
