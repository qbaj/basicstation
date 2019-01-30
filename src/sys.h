// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

#ifndef _sys_h_
#define _sys_h_

#include "rt.h"

enum { PPS_GPS=0, PPS_FUZZY, PPS_TESTPIN };
extern u1_t   sys_modePPS; // special PPS mode?
extern u1_t   sys_deviceMode; // special mode used for GW regr testing
extern u1_t   sys_noTC;
extern u2_t   sys_webPort;
extern s1_t   sys_slaveIdx;   // -1=master, >=0 slave process
extern uL_t   protoEUI;
extern uL_t   prefixEUI;

void  sys_ini ();
void  sys_fatal (int code);
void  sys_addLog (str_t line, int len);     // output/store one log line - *is* always \n treminated
#if defined(CFG_sysrandom)
int  sys_random (u1_t* buf, int len);
#else
void  sys_seed (u1_t* seed, int len);       // sys provides high quality seeds to grow randomness
#endif
sL_t  sys_time ();
sL_t  sys_utc  ();  // native UTC time - return 0 if not avail.
uL_t  sys_eui  ();
void  sys_usleep(sL_t us);

enum {
    SYSIS_TC_CONNECTED    = 1,
    SYSIS_TC_DISCONNECTED = 2,
    SYSIS_STATION_DEAD    = 3,  // process not started
    SYSIS_CUPS_INTERACT   = 4,
    SYSIS_CUPS_DONE       = 5,
};
void sys_inState (int state);

// Categories of credentials/config
enum { SYS_CRED_CUPS, SYS_CRED_TC, SYS_CRED_MAX };  // cat - category
enum { SYS_CRED_REG, SYS_CRED_BAK, SYS_CRED_BOOT }; // set - set of configs
enum { SYS_CRED_TRUST, SYS_CRED_MYCERT, SYS_CRED_MYKEY, SYS_CRED_NELEMS };
enum { SYS_AUTH_NONE, SYS_AUTH_SERVER, SYS_AUTH_BOTH, SYS_AUTH_TOKEN };
str_t sys_credcat2str (int cred_cat);
str_t sys_credset2str (int cred_set);
int   sys_cred (int cred_cat, int cred_set, str_t* elems, int* elemslen);
void  sys_credStart (int cred_cat, int len);
void  sys_credWrite  (int cred_cat, u1_t* data, int off, int len);
void  sys_credComplete (int cred_cat, int len);

void  sys_updateStart  (int len);
void  sys_updateWrite  (u1_t* data, int off, int len);
int   sys_updateCommit (int len);
void  sys_resetConfigUpdate ();
void  sys_commitConfigUpdate ();
void  sys_backupConfig (int cred_cat);

str_t sys_version ();
str_t sys_uri     (int cred_cat, int cred_set);
void  sys_saveUri (int cred_cat, str_t uri);
u4_t  sys_crcCred (int cred_cat);

void   sys_runUpdate ();
void   sys_abortUpdate ();
str_t  sys_radioDevice (str_t device);
int    sys_runRadioInit (str_t device);
int    sys_execCommand (ustime_t max_wait, str_t* argv);

dbuf_t sys_sigKey (int key_id);
u4_t   sys_crcSigkey (int key_id);
dbuf_t sys_readFile (str_t filename);   // should this be here? - only used in sx1301conf.c
str_t  sys_makeFilepath (str_t fn, int complain);

void   sys_iniTC ();
void   sys_stopTC();
void   sys_startTC();
s1_t   sys_statusTC();

void   sys_iniCUPS();
void   sys_triggerCUPS();
void   sys_clearCUPS();
void   sys_delayCUPS();
s1_t   sys_statusCUPS();

void   sys_iniWeb();
void   sys_stopWeb();

void   sys_keepAlive(int fd);

#endif // _sys_h_