# I2C DRIVER

## 1. Giới thiệu

File này mô tả driver I2C được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `i2c.c`: Chứa phần hiện thực các hàm I2C.
- `i2c.h`: Chứa khai báo hàm, kiểu dữ liệu và các định nghĩa cần thiết.
- `clock.h` : Cấp clock cho port sử dụng I2C và I2C.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

I2C Peripheral: `I2C1`

Các chân GPIO: `PB6`  `PB7`

## 3. Cấu hình I2C

Driver cấu hình I2C1 hoạt động ở chế độ Master.

Các thông số:

- Clock I2C: `50MHz` (PCLK1)
- Tốc độ I2C: `100kHz` (STANDARD MODE)
- Chế độ địa chỉ: `7-bit`
- SCL: `PB6`
- SDA: `PB7`

## 4. Các thanh ghi sử dụng

### GPIOB

- GPIOB_MODER
- GPIOB_OTYPER
- GPIOB_OSPEEDR
- GPIOB_PUPDR
- GPIOB_AFRL

### I2C1

- I2C_CR1
- I2C_CR2
- I2C_OAR1
- I2C_DR
- I2C_SR1
- I2C_SR2
- I2C_CCR
- I2C_TRISE

## 5. I2C.h

- Tạo kiểu dữ liệu trả về trạng thái `I2C_Status_t`

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void i2c_init(void)` : hàm cấu hình I2C

    + `I2C_Status_t i2c_mem_write(uint8_t dev_addr, uint8_t mem_addr, const uint8_t *data, uint16_t len)` : Hàm ghi dữ liệu từ một thanh ghi cụ thể của Slave

    + `I2C_Status_t i2c_mem_read(uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint16_t len)` : Hàm đọc dữ liệu từ một thanh ghi cụ thể của Slave

## 6. I2C.c

- Thực hiện các hàm I2C: 

* `i2c_wait_flag_set(volatile uint32_t *reg, uint32_t flag)` : Hàm chờ cờ trạng thái được set lên 1

    + `reg` : địa chỉ thanh ghi chứa bit cờ 

    + `flag`: vị trí bit cờ 

    + `Ví dụ`: `i2c_wait_flag_set(I2C1_SR1, I2C_SR1_TXE)`

* `i2c_clear_addr_flag(void)` : Hàm xóa cờ `ADDR` bằng cách đọc lần lượt thanh ghi `I2C1_SR1` và `I2C1_SR2`

* `i2c_start(void)` : Hàm tạo điều kiện START để bắt đầu quá trình giao tiếp I2C

* `i2c_stop(void)` : Hàm tạo điều kiện STOP để kết thúc quá trình giao tiếp I2C

* `i2c_send_address(uint8_t dev_addr, uint8_t read)` : Hàm gửi địa chỉ 7-bit của Slave và bit Read/Write

    + `dev_addr` : địa chỉ 7-bit của Slave

    + `read` : xác định chế độ truyền dữ liệu, `0` là Write và `1` là Read

    + `Ví dụ` : `i2c_send_address(0x76, 0)` gửi địa chỉ `0x76` ở chế độ Write

* `i2c_init(void)` : Hàm khởi tạo và cấu hình I2C1

    + Cấp clock cho GPIOB và I2C1

    + Cấu hình PB6 làm SCL và PB7 làm SDA

    + Cấu hình PB6 và PB7 ở chế độ Alternate Function AF4

    + Cấu hình chân ở chế độ Open-drain

    + Cấu hình Pull-up cho SCL và SDA

    + Cấu hình PCLK1 = 50 MHz

    + Cấu hình CCR = 250

    + Cấu hình TRISE = 51

    + Cấu hình I2C hoạt động ở Standard Mode với tốc độ 100 kHz

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `i2c_init()`

* `i2c_send_byte(uint8_t data)` : Hàm gửi một byte dữ liệu qua I2C

    + `data` : byte dữ liệu cần gửi

    + `Ví dụ` : `i2c_send_byte(0xF4)` gửi byte dữ liệu `0xF4`

* `i2c_read_byte(uint8_t *data, uint8_t ack)` : Hàm đọc một byte dữ liệu từ Slave

    + `data` : con trỏ đến biến dùng để lưu byte dữ liệu đọc được

    + `ack` : xác định có gửi ACK sau khi nhận dữ liệu hay không, khác `0` là bật ACK và bằng `0` là tắt ACK

    + `Ví dụ` : `i2c_read_byte(&data, 1)`

* `i2c_master_transmit(uint8_t dev_addr, const uint8_t *data, uint16_t len)` : Hàm Master gửi một hoặc nhiều byte dữ liệu đến Slave

    + `dev_addr` : địa chỉ 7-bit của thiết bị Slave

    + `data` : địa chỉ vùng dữ liệu cần gửi

    + `len` : số byte dữ liệu cần gửi

    + `Ví dụ` : `i2c_master_transmit(0x76, data, 3)` gửi 3 byte dữ liệu đến Slave có địa chỉ `0x76`

* `i2c_master_receive(uint8_t dev_addr, uint8_t *data, uint16_t len)` : Hàm Master nhận một hoặc nhiều byte dữ liệu từ Slave

    + `dev_addr` : địa chỉ 7-bit của thiết bị Slave

    + `data` : địa chỉ vùng dữ liệu cần gửi

    + `len` : số byte dữ liệu cần nhận

    + Hàm xử lý riêng các trường hợp đọc `1 byte`, `2 byte` và `nhiều hơn 2 byte`

    + `Ví dụ` : `i2c_master_receive(0x76, data, 6)` đọc 6 byte từ Slave có địa chỉ `0x76`

* `i2c_mem_write(uint8_t dev_addr, uint8_t mem_addr, const uint8_t *data, uint16_t len)` : Hàm ghi dữ liệu vào một thanh ghi cụ thể của Slave

    + `dev_addr` : địa chỉ 7-bit của thiết bị Slave

    + `mem_addr` : địa chỉ thanh ghi bên trong Slave cần ghi dữ liệu

    + `data` : địa chỉ vùng dữ liệu cần ghi

    + `len` : số byte dữ liệu cần ghi

    + `Ví dụ` : `i2c_mem_write(0x76, 0xF4, &data, 1)` ghi 1 byte dữ liệu vào thanh ghi `0xF4` của Slave có địa chỉ `0x76`

* `i2c_mem_read(uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint16_t len)` : Hàm đọc dữ liệu từ một thanh ghi cụ thể của Slave

    + `dev_addr` : địa chỉ 7-bit của thiết bị Slave

    + `mem_addr` : địa chỉ thanh ghi bên trong Slave cần đọc dữ liệu

    + `data` : địa chỉ vùng nhớ dùng để lưu dữ liệu đọc được

    + `len` : số byte dữ liệu cần đọc

    + `Ví dụ` : `i2c_mem_read(0x76, 0xD0, &data, 1)` đọc 1 byte từ thanh ghi `0xD0` của Slave có địa chỉ `0x76`