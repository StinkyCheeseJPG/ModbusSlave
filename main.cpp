#include "main.h"

int main() {
    // 取得設定檔內初始設定(Slave 監聽的串口,slaveID).
    settxt initSet("ini.txt");
    deviceRTU = initSet.getValue("RTUDevice", "/dev/pts/2");
    slaveID = initSet.getValue("SlaveID", "1");

    // 創建 Modbus RTU Slave
    ctx = modbus_new_rtu(deviceRTU.c_str(), 9600, 'N', 8, 1);
    if (ctx == nullptr) {
        std::cerr << "Failed to create Modbus RTU context\n";
        return -1;
    }

    modbus_set_slave(ctx, atoi(slaveID.c_str()));

    if (modbus_connect(ctx) == -1) {
        std::cerr << "Failed to connect to " << deviceRTU << "\n";
        modbus_free(ctx);
        return -1;
    }

    // 設定 Modbus 超時，避免 modbus_receive()之後卡住.
    modbus_set_response_timeout(ctx, 1, 0);  // 1 秒超時

    // 設定 Modbus 暫存區.
    mb_mapping = modbus_mapping_new(256, 256, 128, 128);  // 記憶體空間.
    if (mb_mapping == nullptr) {
        std::cerr << "Failed to allocate Modbus mapping\n";
        modbus_free(ctx);
        return -1;
    }

    std::cout << "Modbus RTU Slave is running on " << deviceRTU << "\n";

    uint8_t query[MODBUS_RTU_MAX_ADU_LENGTH];
    while (true) {
        int rc = modbus_receive(ctx, query);
        if (rc > 0) {
            if (query[1] == MODBUS_FC_MASK_WRITE_REGISTER){
                std::fill(mb_mapping->tab_registers, mb_mapping->tab_registers + 256, 0);
            }
            modbus_reply(ctx, query, rc, mb_mapping);
        }
        else if (rc == -1) {
            std::cerr << "Connection lost\n";
            break;
        }
    }

    // 清理資源
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
