// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#ifndef _ralsub_h_
#define _ralsub_h_
#if defined(CFG_lgw1) && defined(CFG_ral_master_slave)

#include "timesync.h"


enum {
    RAL_CMD_CONFIG = 1,
    RAL_CMD_TXSTATUS,
    RAL_CMD_TXABORT,
    RAL_CMD_TX,
    RAL_CMD_TX_NOCCA,
    RAL_CMD_RX,
    RAL_CMD_TIMESYNC,
    RAL_CMD_STOP,
};

struct ral_header {
    sL_t rctx;
    u1_t cmd;
};

struct ral_timesync_req {
    sL_t rctx;
    u1_t cmd;
};

struct ral_stop_req {
    sL_t rctx;
    u1_t cmd;
};

struct ral_txstatus_req {
    sL_t rctx;
    u1_t cmd;
    u1_t status; // struct length needs to align with resp
};

struct ral_txabort_req {
    sL_t rctx;
    u1_t cmd;
};

struct ral_config_req {
    sL_t rctx;
    u1_t cmd;
    u2_t jsonlen;
    u4_t region;   // 0=no LBT, !=0 LBT for this region
    char hwspec[MAX_HWSPEC_SIZE];
    char json[PIPE_BUF-16-MAX_HWSPEC_SIZE];  // 16 >= 8+1+2+4
};

struct ral_tx_req {
    sL_t  rctx;
    u1_t  cmd;
    u1_t  txlen;
    u1_t  txpow;
    rps_t rps;
    u4_t  freq;
    sL_t  xtime;
    u1_t  txdata[MAX_TXFRAME_LEN];
};

// Generic response - status
// tx:       RAL_TX_{OK,FAIL,NOCA}
// cca:      0=busy, 1=clear
// txstatus: TX status code
// config:   0=fail, 1=ok
struct ral_response {
    sL_t rctx;
    u1_t cmd;
    u1_t status;
};

struct ral_timesync_resp {
    sL_t rctx;
    u1_t cmd;
    int  quality;
    timesync_t timesync;
};

struct ral_rx_resp {
    sL_t  rctx;
    u1_t  cmd;
    u1_t  rxlen;
    rps_t rps;
    u4_t  freq;
    sL_t  xtime;
    u1_t  rssi;   // scaled RSSI (*-1)
    s1_t  snr;    // scaled SNR (*8)
    u1_t  rxdata[MAX_RXFRAME_LEN];
};

// Fwd decl.
struct lgw_pkt_tx_s;
struct lgw_pkt_rx_s;

rps_t ral_lgw2rps (struct lgw_pkt_rx_s* p);
void  ral_rps2lgw (rps_t rps, struct lgw_pkt_tx_s* p);


#endif // defined(CFG_lgw1) && defined(CFG_ral_master_slave)
#endif // _ralsub_h_