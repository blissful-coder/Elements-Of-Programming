# from jenkinsapi.jenkins import Jenkins
# import os 



# def get_server_instance():
#     jenkins_url = 'https://jenkins.ml.only.sap'
#     server = Jenkins(jenkins_url, username='I323878', password='116d154054da5c2fd6fe72dee2a3761b3d')
#     return server

# if __name__ == '__main__':
#     os.environ["PYTHONHTTPSVERIFY"] = "0"
#     print(os.environ)
#     print(get_server_instance().version)


import requests

url = "https://jenkins.ml.only.sap/job/AI-Foundation/job/berlin-jenkins/job/scratchpad_2/build"

payload={}
headers = {
  'Jenkins-Crumb': '1933fcea975eced2b5f9cdd4b64a35894c5729ddfa8c7ce95815b72cc3e4e17d',
  'Authorization': 'Basic STMyMzg3ODoxMTZkMTU0MDU0ZGE1YzJmZDZmZTcyZGVlMmEzNzYxYjNk',
  'Cookie': 'JSESSIONID.563f94d8=node01io9copzczo5xbn23637nh3kb8187.node0'
}

response = requests.request("POST", url, headers=headers, data=payload, verify=False)

print(response.text)
