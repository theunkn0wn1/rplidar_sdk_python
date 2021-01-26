import typing

import attr

from ._core import _rplidar_sdk


class DriverError(RuntimeError):
    """ Error response from driver """


@attr.dataclass(frozen=True)
class DeviceInfo:
    model: int
    firmware_version: int
    hardware_version: int
    serialnum: typing.List[int]


@attr.dataclass(frozen=True)
class ResponseMeasurementNodeHq:
    angle_z_q14: int
    dist_mm_q2: int
    quality: int
    flag: int


class Lidar:
    def __init__(self):
        self._driver = _rplidar_sdk.LidarDriver()

    def is_connected(self) -> bool:
        status = self._driver.is_connected()
        if _rplidar_sdk.is_fail(status):
            raise DriverError(
                "got error response from driver! raw:= {}".format(status)
            )
        return status

    def start_motor(self) -> int:
        status = self._driver.start_motor()
        if _rplidar_sdk.is_fail(status):
            raise DriverError(
                "got error response from driver! raw:= {}".format(status)
            )
        return status

    def stop_motor(self) -> int:
        status = self._driver.stop_motor()
        if _rplidar_sdk.is_fail(status):
            raise DriverError(
                "got error response from driver! raw:= {}".format(status)
            )
        return status

    def connect(self, port: str, baud: int = 9600, flags: int = 0) -> int:
        status = self._driver.connect(port, baud, flags)
        if _rplidar_sdk.is_fail(status):
            raise DriverError(
                "got error response from driver! raw:= {}".format(status)
            )
        return status

    def disconnect(self) -> None:
        return self._driver.disconnect()

    def read(self) -> typing.Iterable[ResponseMeasurementNodeHq]:
        raw_data = self._driver.read()
        return (ResponseMeasurementNodeHq(*node) for node in raw_data)

    def get_device_info(self) -> typing.Tuple[int, DeviceInfo]:
        status, raw_data = self._driver.get_device_info()
        data = DeviceInfo(
            model=raw_data.model,
            firmware_version=raw_data.firmware_version,
            hardware_version=raw_data.hardware_version,
            serialnum=raw_data.serialnum
        )
        return status, data
