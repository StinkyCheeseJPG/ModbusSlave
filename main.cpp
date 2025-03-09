#include "main.h"

int main() {
    // ���o�]�w�ɤ���l�]�w(Slave ��ť����f,slaveID).
    settxt initSet("ini.txt");
    deviceRTU = initSet.getValue("RTUDevice", "/dev/pts/2");
    slaveID = initSet.getValue("SlaveID", "1");

    // �Ы� Modbus RTU Slave
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

    // �]�w Modbus �W�ɡA�קK modbus_receive()����d��.
    modbus_set_response_timeout(ctx, 1, 0);  // 1 ��W��

    // �]�w Modbus �Ȧs��.
    mb_mapping = modbus_mapping_new(256, 256, 128, 128);  // �O����Ŷ�.
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

    // �M�z�귽
    modbus_mapping_free(mb_mapping);
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}
