//
// Created by marin on 08.03.2025.
//

/**
 * The communication between microcontrollers uses I2C protocol.
 * The following enums define the I2C buffer registers for each slave.
 * During a transaction, these addresses will be specified after the slave own address.
 * Each data transfer is 4-byte long (32-bit)
 * 
 * Intranet reference: https://docs.google.com/spreadsheets/d/159JLAAPnOQsqaWHLeamU7fWXOPAsgL0OkVv0sn9sXFg/edit?gid=0#gid=0
 */

#ifndef AV_INTRANET_COMMANDS_H
#define AV_INTRANET_COMMANDS_H

/* Slaves addresses */
#define NET_ADR_DPR_ETH 0x0E
#define NET_ADR_DPR_LOX 0x0C
#define NET_ADR_PRB     0x0F
#define NET_ADR_TRB     0x0A

/* Engine valves map */
#define PRB_VO_NOC (1 << 5)
#define PRB_VE_NO  (1 << 4)  
#define PRB_IO_NCC (1 << 3)
#define PRB_IE_NC  (1 << 2)
#define PRB_MO_BC  (1 << 1)
#define PRB_ME_B   (1 << 0)

/* For boolean data type, such as WAKE_UP */
#define ON  0xAC  // Activate
#define OFF 0xDE  // Deactivate

/* Havoc DPR */
enum NET_REG_DPR {
    TIMESTAMP_MAIN = 0x00, // W
    WAKE_UP        = 0x01, // W
    IS_WOKEN_UP    = 0x02, // R
    PRESSURIZE     = 0x03, // W
    ABORT          = 0x04, // W
    PRESSURE       = 0x05, // R
    DN_NC          = 0x06  // R
};

/* Prop Board */
enum NET_REG_PRB {
    TIMESTAMP_MAIN  = 0x00, // W
    WAKE_UP         = 0x01, // W
    IS_WOKEN_UP     = 0x02, // R
    CLEAR_TO_IGNITE = 0x03, // W
    FSM_PRB         = 0x04, // R
    P_OIN           = 0x05, // R
    T_OIN           = 0x06, // R
    P_EIN           = 0x07, // R
    T_EIN           = 0x07, // R
    P_CCC           = 0x08, // R
    T_CCC           = 0x09, // R
    P_CIG           = 0x0A, // R
    T_CIG           = 0x0B, // R
    VALVES_STATE    = 0x0C  // R/W
};

/* Trigger Board */
enum class NET_REG_TRB {
    TIMESTAMP_MAIN   = 0x00, // W
    WAKE_UP          = 0x01, // W
    IS_WOKEN_UP      = 0x02, // R
    CLEAR_TO_TRIGGER = 0x03, // W
    PYRO_CH1         = 0x04, // R/W
    PYRO_CH2         = 0x05, // R/W
    PYRO_CH3         = 0x06  // R/W
};

/* Cameras */
// enum class NET_REG_CAM {
//     TIMESTAMP_MAIN = 0x00, // W
//     WAKE_UP        = 0x01, // W
//     IS_WOKEN_UP    = 0x02, // R
//     RECORDING      = 0x03  // R/W
// };

#endif /* AV_INTRANET_COMMANDS_H */
