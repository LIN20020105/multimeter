#include "send.h"
#include "string.h"
#include "math.h"
#include "usart.h"


//const u32 UUID32 = 0x12345678;
u32 UUID32 = 0;
const char* SERVER_ADDRESS = "tcp://182.254.211.28:1883";
const char* CLIENT_ID = "mqtt_multimeter_terminal";
const char* TOPIC = "/fzu/multimeter";
uint32_t CpuID[3];							//小端模式
uint32_t hashed_value = 0;

uint32_t get_now_timestamp() {
return 0;
}

void resetReporter(ReportStruct *log) { memset(log, 0, sizeof(ReportStruct)); }//clean

//define pack
void pack(ReportStruct *log,u32 uid,u8 O1,u8 O2,u8 O3,u32 U1,u32 U2,u32 U3) {

  log->timestamp = get_now_timestamp();
  log->header = 0x95278023;
  log->deviceId = uid;
  log->o1 = O1, log->o2 = O2, log->o3 = O3;
  log->U1 = U1, log->U2 = U2, log->U3 = U3;

  u32 check = 0;
  check ^= log->deviceId;
  check += log->timestamp;
  check += log->header;
  check += log->o1 + log->o2 + log->o3;
  check += log->U1 + log->U2 + log->U3;
  log->checkSum = check;
}

void GetChipID ( void )
{
    CpuID[0] = * ( uint32_t * ) ( 0x1ffff7e8 ); //高32位地址
    CpuID[1] = * ( uint32_t * ) ( 0x1ffff7ec ); //中32位地址
    CpuID[2] = * ( uint32_t * ) ( 0x1ffff7f0 ); //低32位地址
}
uint32_t murmur3_32_simple(uint32_t k) {
    k ^= k >> 16;
    k *= 0x85ebca6b;
    k ^= k >> 13;
    k *= 0xc2b2ae35;
    k ^= k >> 16;
    return k;
}
uint32_t hash_cpu_id(uint32_t cpu_id0, uint32_t cpu_id1, uint32_t cpu_id2) {
    uint64_t combined_id = ((uint64_t)cpu_id0 << 32) | cpu_id1;
    combined_id ^= cpu_id2;

    uint32_t hash = murmur3_32_simple(combined_id & 0xFFFFFFFF);
    hash ^= murmur3_32_simple(combined_id >> 32);

    // 取模到 0-999999
    return hash % 1000000;
}
//define reporter
ReportStruct reporter;
//fill reporter
void fillReportData(u8 O1,u8 O2,u8 O3,u32 U1,u32 U2,u32 U3) {
//	UUID32 = HAL_GetDEVID();
	GetChipID();
	hashed_value = hash_cpu_id(CpuID[0], CpuID[1], CpuID[2]);
	hashed_value = hashed_value * 10;
     resetReporter(&reporter);
    pack(&reporter, hashed_value, O1, O2, O3, U1, U2, U3);
  HAL_UART_Transmit(&huart1, (uint8_t *)&reporter, sizeof(reporter), HAL_MAX_DELAY);
}
