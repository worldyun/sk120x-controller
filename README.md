# sk120x-controller

`sk120x-controller` 是一个基于 `Arduino` 框架的嵌入式控制系统，专为控制 `SK120X` 设备而设计。该项目使用 ESP32-C3 微控制器平台，并通过 BLE（蓝牙低功耗）协议与外部设备进行通信。

---

## 📌 项目概述

本项目的主要功能是通过 BLE 控制 SK120X 设备，包括：

- **BLE 通信**：提供 BLE 服务和特征值，支持读写寄存器、获取设备状态等功能。
- **ModBus RTU 通信**：通过 ModBus 协议与 SK120X 设备通信，实现对设备寄存器的读写操作。
- **自动数据采集**：定时读取设备常用寄存器，并通过 BLE 通知客户端。
- **日志记录**：使用 `ArduinoLog` 库记录详细的运行日志，便于调试和分析。

## 📊 配套移动端上位机软件
- [sk120x-controller-app](https://github.com/worldyun/sk120x-controller-app)

---

## 🧩 核心组件

### 1. **BLE 模块 (`BLE.h/.cpp`)**
- 初始化 BLE 服务和特征值。
- 提供连接/断开回调。
- 支持以下特征值：
  - 获取所有配置
  - 设置配置
  - 通知前10个寄存器值
- 使用 FreeRTOS 创建 BLE 通知任务。

### 2. **SKDevice 模块 (`SKDevice.h/.cpp`)**
- 封装 SK120X 设备的 ModBus 操作。
- 支持读写寄存器、初始化串口等。
- 使用互斥锁保证线程安全。
- 自动读取常用寄存器。

### 3. **UserService 模块 (`UserService.h/.cpp`)**
- 处理来自 BLE 的命令请求。
- 根据功能码执行对应操作：
  - 读取单个/多个寄存器
  - 写入寄存器
  - 读取全部寄存器

### 4. **BLEWriteData 模块 (`BLEWriteData.h/.cpp`)**
- 解析 BLE 写入的数据包。
- 提取功能码、寄存器地址和数据内容。

### 5. **日志模块 ([log_init.h](https://github.com/worldyun/sk120x-controller/tree/main/include/log_init.h), `utils/log.h`)**
- 基于 `ArduinoLog` 实现日志输出。
- 支持多种日志级别（INFO, ERROR, WARNING 等）。
- 输出时间戳和调用上下文信息。

---

## ⚙️ 配置选项 ([config.h](https://github.com/worldyun/sk120x-controller/tree/main/include/config.h))

项目中可通过 [config.h](https://github.com/worldyun/sk120x-controller/tree/main/include/config.h) 修改以下参数：

- BLE 服务 UUID 和特征值 UUID
- BLE 广播功率、MTU 大小
- SK120X 设备串口引脚和波特率
- ModBus 地址
- 日志级别
- 寄存器自动读取间隔
- 可写寄存器地址列表
- 是否启用寄存器写入验证

---

## 📦 依赖库

- [Arduino](https://www.arduino.cc/)
- [DFRobot_RTU](https://github.com/DFRobot/DFRobot_RTU)：用于 ModBus RTU 通信

---

## 📁 项目结构

```
.
├── include/                # 头文件目录
│   ├── BLE.h
│   ├── SKDevice.h
│   ├── config.h             # 配置文件
│   ├── utils/
│   │   └── log.h            # 日志宏定义
│   └── ...
├── src/                    # 源代码目录
│   ├── BLE.cpp
│   ├── SKDevice.cpp
│   ├── UserService.cpp
│   ├── BLEWriteData.cpp
│   └── main.cpp
├── lib/                    # 第三方库（PlatformIO 自动管理）
└── platformio.ini          # PlatformIO 项目配置文件
```

---

## 🛠️ 开发环境

- IDE: VSCode + PlatformIO
- 主控芯片: ESP32-C3
- 编译框架: Arduino for ESP32

---

## 📜 构建与烧录

使用 PlatformIO 构建并上传项目：

```bash
pio run -t upload
```

---

## 📊 功能演示

1. BLE 连接后可读取 SK120X 所有寄存器。
2. 支持通过 BLE 设置电压、电流等参数。
3. 定时自动读取常用寄存器并通过 BLE 通知客户端。
4. 支持日志输出，方便调试和问题追踪。

---

## 📝 注意事项

- BLE 服务需在手机或其他 BLE 客户端上扫描并连接。推荐使用此项目配套的移动端上位机软件[sk120x-controller-app](https://github.com/worldyun/sk120x-controller-app)。
- SK120X 设备需通过[UART接口](https://github.com/worldyun/sk120x-controller/tree/main/include/config.h#L53-L57)与 ESP32-C3 正确连接。
- 若更改 ModBus 地址，请确保 [CONFIG_SK_DEVICE_MODBUS_ADDRESS](https://github.com/worldyun/sk120x-controller/tree/main/include/config.h#L65-L66) 与设备一致。
- 如需禁用寄存器写入验证，可在 [config.h](https://github.com/worldyun/sk120x-controller/tree/main/include/config.h) 中注释 `CONFIG_SK_DEVICE_REGISTERS_WRITE_VERIFY_ENABLE`。

---

如需进一步扩展功能或优化性能，欢迎提交 PR 或 Issue！