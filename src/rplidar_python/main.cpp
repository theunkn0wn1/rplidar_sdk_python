
#include "main.h"
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

  py::list read() {
    this->assert_driver();

    py::list points;
    std::array<rplidar_response_measurement_node_hq_t,
               rp::standalone::rplidar::RPlidarDriver::MAX_SCAN_NODES>
        nodes = {};

    this->_driver->startScan(false, true);
    this->start_motor();
    size_t max_nodes = nodes.size();
    auto scan_result = this->_driver->grabScanDataHq(nodes.data(), max_nodes);
    this->stop_motor();

    if (IS_FAIL(scan_result)) {
      throw std::runtime_error("scan failed!");
    }
    this->_driver->ascendScanData(nodes.data(), max_nodes);

    // convert to a python tupple
    for (const auto &node : nodes) {
      points.append(pybind11::make_tuple(node.angle_z_q14, node.dist_mm_q2,
                                         node.flag, node.quality));
    }
    return points;
  }
};

PYBIND11_MODULE(_core, module) {
  module.doc() = "Python bindings to the RPLIDAR C++ sdk";
  module.def("is_ok", &is_ok, "returns whether the rplidar return is OK");
  module.def("is_fail", &is_fail,
             "returns whether the rplidar return is a FAIL");
  py::class_<Lidar>(module, "LidarDriver")
      .def(py::init())
      .def("is_connected", &Lidar::is_connected)
      .def("start_motor", &Lidar::start_motor)
      .def("stop_motor", &Lidar::stop_motor)
      .def("connect", &Lidar::connect)
      .def("disconnect", &Lidar::disconnect)
      .def("read", &Lidar::read)
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
/// Thin wrapper around the IS_OK preprocessor directive as it is a lvalue
/// and we can only bind rvalues
/// \param value to check
/// \return if the value is OK or not according to rplidar
bool is_ok(uint32_t value) { return IS_OK(value); }

bool is_fail(uint32_t value) { return IS_FAIL(value); }