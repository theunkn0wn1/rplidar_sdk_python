from typing import List, Tuple


class LidarDriver:
    def is_connected(self) -> bool:
        ...

    def start_motor(self) -> int:
        ...

    def stop_motor(self) -> int:
        ...

    def connect(self, port: str, baud: int = 9600, flags: int = 0) -> int:
        ...

    def disconnect(self) -> None:
        ...

    def read(self) -> List[Tuple[int, int, int, int]]:
        ...

    def get_device_info(self) -> Tuple[int, DeviceInfo]:
        ...


class DeviceInfo:
    @property
    def model(self) -> int:
        ...

    @property
    def firmware_version(self) -> int:
        ...

    @property
    def hardware_version(self) -> int:
        ...

    @property
    def serialnum(self) -> List[int]:
        ...

def is_fail(value: int) -> bool:
    ...

def is_ok(value: int) -> bool:
    ...
