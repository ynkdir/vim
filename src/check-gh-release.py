#!/usr/bin/python3

# Check if one day or more has been past since the last GH release.
#
# returns: 0 - one day or more past
#          1 - not past

import urllib.request, urllib.error
import json
import os
from io import StringIO
from datetime import datetime, timedelta

default_repo_name = 'vim/vim'
repo_name = os.getenv('APPVEYOR_REPO_NAME', default_repo_name)
repo_tag_name = os.getenv('APPVEYOR_REPO_TAG_NAME', '<dummy>')

gh_release_url = 'https://api.github.com/repos/' + repo_name + '/releases/latest'

try:
    response = urllib.request.urlopen(gh_release_url)
except urllib.error.HTTPError:
    print('GitHub release not found.')
    exit(0)

rel_info = json.load(StringIO(str(response.read(), 'utf-8')))
print('Last release: ' + rel_info['created_at'])

if rel_info['name'] == repo_tag_name:
    # Maybe the second pass of the same build.
    exit(0)

rel_time = datetime.strptime(rel_info['created_at'], '%Y-%m-%dT%H:%M:%SZ')
if datetime.utcnow() > rel_time + timedelta(days=1):
    # One day or more has been past since the last GitHub release.
    exit(0)
else:
    # Not passed.
    exit(1)
