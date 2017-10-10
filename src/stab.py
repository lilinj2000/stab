#!/usr/bin/env python

import json

sink1 = {
    "sink": {
        "type": "stdout_sink_mt",
        "level": "trace"
        }
    }

sink2 = {
    "sink": {
        "type": "rotating_file_sink_mt",
        "file_name": "logs/stab.log",
        "max_file_size": 5000000,
        "max_files": 10
        }
    }

log = {
    "level": "trace",
    "sinks": [sink1, sink2]
    }

sea_trader = { 
    "svr_address": "172.31.0.26",
    "svr_port": 20000,
    "qry_address": "172.31.0.27",
    "qry_port": 20001,
    "user_id": "88991042d",
    "password": "1",
    "prod_info": "tester",
    "mac_addr": "00:0F:53:35:BA:10",
    "account_id": "88991042",
    # 100-sh     101-sz
    # 102-cffex  103-shfe
    # 104-dce    105-zcze
    "exchange_id": 103
    }

stab = {
    "instru": "cu1712",
    "price": 34540,
    "volume": 10,
    "order_counter": 1,
    "order_interval": 2000,
    "timestamp_file": "stab_timestamp.data"
    }

cfg = {
    "stab": stab,
    "sea_trader": sea_trader,
    "log": log
    }

with open('stab.json', 'w') as f:
    json.dump(cfg, f, sort_keys=True, indent=4)
