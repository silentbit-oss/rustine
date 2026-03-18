import json
import sys

args = sys.argv[1:]
path = args[0]

with open(path, 'r') as file:
    json_data = file.read()

json_objects = [line.strip() for line in json_data.strip().split('}\n{')]


cc = 0.0
cog = 0.0
hal = 0.0
mei = 0.0
nargs = 0.0
nexit = 0.0

for i, json_str in enumerate(json_objects, 1):
    js = ""
    if len(json_objects) == 1:
        js = json_str
    else:
        if i == 1:
            js = json_str + '}'
        elif i == len(json_objects):
            js = '{' + json_str
        else:
            js = '{' + json_str + '}'

    data = json.loads(js)
    metrics = data.get('metrics', {})

    cc += 0 if metrics["cyclomatic"]["average"] is None else metrics["cyclomatic"]["average"]
    cog += 0 if metrics["cognitive"]["average"] is None else metrics["cognitive"]["average"]
    hal += 0 if metrics["halstead"]["difficulty"] is None else metrics["halstead"]["difficulty"]
    mei += 0 if metrics["mi"]["mi_sei"] is None else metrics["mi"]["mi_sei"]
    nargs += 0 if metrics["nargs"]["average"] is None else metrics["nargs"]["average"]
    nexit += 0 if metrics["nexits"]["average"] is None else metrics["nexits"]["average"]

code_quality = {}
code_quality["cyclomatic"] =  cc / len(json_objects)
code_quality["cognitive"] =  cog / len(json_objects)
code_quality["difficalty"] = hal / len(json_objects)
code_quality["maintainablitly"] = mei / len(json_objects)
code_quality["number_of_args"] = nargs / len(json_objects)
code_quality["number_of_exit"] = nexit / len(json_objects)

print(json.dumps(code_quality, indent=4))
