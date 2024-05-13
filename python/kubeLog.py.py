import json

def file_data(filename):
    f = open(filename,"r")
    log = f.read()
    return log

def parse_log_to_json(log_data):
    result = {}
    i = 0
    for line in log_data.split('\n'):
        if(line):
            try:
                result[i] = json.loads(line)
                i+=1
            except:
                pass

    return result

def mass_PUT_request(log_obj,subaccount):
    # print(log_obj)
    for key, val in log_obj.items():
        if 'msg' in val and val['msg'] == 'MaaS PUT request':
            return give_measures(val['req.Body'], subaccount)

def give_measures(search_space,subaccount):
    # print(search_space)
    reqobj = json.loads(search_space)
    for key, val in reqobj.items():
        for item in val:
            if('consumer' in item and item['consumer']['subAccount'] == subaccount):
                return item['measures']

log_obj = parse_log_to_json(file_data("log.json"))
# print(log_obj)
print(mass_PUT_request(log_obj,"dummy val"))