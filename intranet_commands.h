//
// Created by marin on 08.03.2025.
// Maintained by AV team.
//

/**
 * The communication between microcontrollers inside Firehorn uses I2C protocol.
 * This file defines the I2C device and register addresses for each slave present on the main AV bus.
 * To simplify things, each read/write operation involves 4 bytes of data (32-bit)
 * 
 * Intranet reference: https://docs.google.com/spreadsheets/d/159JLAAPnOQsqaWHLeamU7fWXOPAsgL0OkVv0sn9sXFg/edit?gid=0#gid=0
 */

#ifndef AV_INTRANET_COMMANDS_H
#define AV_INTRANET_COMMANDS_H

/* Device addresses */
#define AV_NET_ADDR_DPR_ETH  0x0E
#define AV_NET_ADDR_DPR_LOX  0x0C
#define AV_NET_ADDR_PRB      0x0F
#define AV_NET_ADDR_TRB      0x0A
#define AV_NET_ADDR_CAM_SEP  0x1C
#define AV_NET_ADDR_CAM_UP   0x2C
#define AV_NET_ADDR_CAM_DOWN 0x3C

/* Bitshifts */
#define AV_NET_SHIFT_DN_NC 16
#define AV_NET_SHIFT_PX_NC 8
#define AV_NET_SHIFT_VX_NO 0
#define AV_NET_SHIFT_MO_BC 8
#define AV_NET_SHIFT_ME_B  0
#define AV_NET_SHIFT_PYRO3 16
#define AV_NET_SHIFT_PYRO2 8
#define AV_NET_SHIFT_PYRO1 0

/* Valves map */
// DPRs
#define AV_NET_DPR_VALVE_DN_NC  (0xFF << AV_NET_SHIFT_DN_NC) // COPV vent
#define AV_NET_DPR_VALVE_PX_NC  (0xFF << AV_NET_SHIFT_PX_NC)  // Tank pressure regulation
#define AV_NET_DPR_VALVE_VX_NO  (0xFF << AV_NET_SHIFT_VX_NO)  // Tank vent
// PRB
#define AV_NET_PRB_VALVE_MO_BC  (0xFF << AV_NET_SHIFT_MO_BC)
#define AV_NET_PRB_VALVE_ME_B   (0xFF << AV_NET_SHIFT_ME_B)

/* Pyro channels map */
#define AV_NET_TRB_PYRO3 (0xFF << AV_NET_SHIFT_PYRO3) 
#define AV_NET_TRB_PYRO2 (0xFF << AV_NET_SHIFT_PYRO2)
#define AV_NET_TRB_PYRO1 (0xFF << AV_NET_SHIFT_PYRO1)

/* For boolean data type, such as the valves */
#define AV_NET_CMD_ON  0x64  // Activate/Open
#define AV_NET_CMD_OFF 0x0D  // Deactivate/Close

/* Each I2C packet involves 4-bytes of data */
#define AV_NET_XFER_SIZE 4

/* Register addresses */ 
// Havoc DPR
enum AV_NET_REG_DPR {
    AV_NET_DPR_TIMESTAMP      = 0x00, // -W
    AV_NET_DPR_PRESSURIZE     = 0x01, // -W
    AV_NET_DPR_ABORT          = 0x02, // -W
    AV_NET_DPR_P_XTA          = 0x03, // R-  Tank pressure
    AV_NET_DPR_T_XTA          = 0x04, // R-  Tank temp
    AV_NET_DPR_P_NCO          = 0x05, // R-  COPV pressure
    AV_NET_DPR_T_NCO          = 0x06, // R-  COPV temp
    AV_NET_DPR_T_COPV_EXT     = 0x07, // R-  COPV External temp (DPR_ETH T_EIN)
    AV_NET_DPR_T_FLS_90       = 0x08, // R-  LOx Ullage how (DPR_ETH T_OIN)
    AV_NET_DPR_T_FLS_80       = 0x09, // R-  LOx Ullage low (DPR_LOX T_EIN)
    AV_NET_DPR_T_FLS_50       = 0x0A, // R-  LOx Tank mid (DPR_LOX T_OIN)
    AV_NET_DPR_VALVES_STATE   = 0x0B, // RW
    AV_NET_DPR_PASSIVATE      = 0x0C, // -W
    AV_NET_DPR_RESET          = 0x0D, // -W
    AV_NET_DPR_NB_REG
};

// ============== Prop Board CMD ===============
enum AV_NET_REG_PRB {
    AV_NET_PRB_TIMESTAMP       = 0x00, // -W
    AV_NET_PRB_CLEAR_TO_IGNITE = 0x01, // -W
    AV_NET_PRB_FSM_PRB         = 0x02, // R-
    AV_NET_PRB_ABORT           = 0x03, // -W    On to passivate Off when on ground
    AV_NET_PRB_P_OIN           = 0x04, // R-
    AV_NET_PRB_P_EIN           = 0x05, // R-
    AV_NET_PRB_T_EIN           = 0x06, // R-
    AV_NET_PRB_P_CCC           = 0x07, // R-
    AV_NET_PRB_T_CCC           = 0x08, // R-
    AV_NET_PRB_T_FLS_10        = 0x09, // R-  (PRB T_EIN PT1000)
    AV_NET_PRB_T_FLS_0         = 0x0A, // R-  (PRB T_OIN PT1000)
    AV_NET_PRB_VALVES_STATE    = 0x0B, // RW
    AV_NET_PRB_IGNITER         = 0x0C, // RW
    AV_NET_PRB_SPECIFIC_IMP    = 0x0D, // R-
    AV_NET_PRB_PASSIVATE       = 0x0E, // -W
    AV_NET_PRB_RESET           = 0x0F, // -W
    AV_NET_PRB_PRESSURE_CHECK  = 0x10, // R-
    AV_NET_PRB_NB_REG
};

// =============== Prop Board FSM ===============
enum PRB_FSM {
    IDLE,                       // Wait for order from FC & collect data from sensors
    CLEAR_TO_IGNITE,            // Wait for ignition order & only state from which the ignition can be triggered
    IGNITION_SQ,                // Execute ignition sequence
    PASSIVATION_SQ,             // Execute shutdown sequence
    ABORT,                      // Abort current operation
    ERROR
};

// Trigger Board
enum AV_NET_REG_TRB {
    AV_NET_TRB_TIMESTAMP        = 0x00, // -W
    AV_NET_TRB_WAKE_UP          = 0x01, // -W
    AV_NET_TRB_IS_WOKEN_UP      = 0x02, // R-
    AV_NET_TRB_CLEAR_TO_TRIGGER = 0x03, // -W
    AV_NET_TRB_PYROS            = 0x04, // RW
    AV_NET_TRB_HAS_TRIGGERED    = 0x05, // R-
    AV_NET_TRB_RESET            = 0x06, // -W
    AV_NET_TRB_NB_REG
};

// Cameras
enum AV_NET_REG_CAM {
    AV_NET_CAM_TIMESTAMP      = 0x00, // -W
    AV_NET_CAM_RECORDING      = 0x01, // RW
    AV_NET_CAM_POWER          = 0x02  // RW
};

#endif /* AV_INTRANET_COMMANDS_H */
