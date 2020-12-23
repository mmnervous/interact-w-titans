# curl -X POST --data '{"jsonrpc":"2.0","method":"int_getBalance","params":["INT3HcmxkEx7dDRwVHqEVV46v1dYFsyd", "latest"],"id":1}' -H 'content-type: application/json;' http://localhost:8555/testnet

import requests

headers = {
    'content-type': 'application/json;'
}

getBalance = '{"jsonrpc":"2.0","method":"int_getBalance","params":["INT3HcmxkEx7dDRwVHqEVV46v1dYFsyd", "latest"],"id":1}'

response = requests.post('http://localhost:8555/testnet', headers=headers, data=getBalance)

print(response.text)
