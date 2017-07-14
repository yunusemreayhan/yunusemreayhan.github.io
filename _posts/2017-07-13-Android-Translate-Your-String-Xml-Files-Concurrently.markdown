---
layout: post
title: string.xml Translations Using Google Apis
author: Yunus Emre AYHAN
date:   2017-07-13 23:48:00
categories: Python Android
comments: true
---

Hello community,

This is a simple translation code writen in python. This simple sweet tool can tranlate your applications with google tranlate abilities within minutes. Check it out. By the way, in order to use it you will need to install google api stuff, here is the [link](https://developers.google.com/api-client-library/)

### KOD :

```python
#!/usr/bin/python
# -*- coding: utf-8 -*-
import shutil
import os
from queue import Queue

threadcount = 5
q = Queue(maxsize=0)

sourcedoc="~/Documents/repos/Timer/app/src/main/res/values/strings.xml"
outfolder="~/Documents/repos/Timer/app/src/main/res/"


def translate(tranlate_text, targetlang):
    from google.cloud import translate
    translate_client = translate.Client()
    translation = translate_client.translate(
        tranlate_text,
        target_language=targetlang)
    return translation['translatedText']

def get_languages():
    from google.cloud import translate
    translate_client = translate.Client()
    return translate_client.get_languages()

def translate_file(targetlang):
    import xml.etree.ElementTree as ET
    outputfolder = outfolder + "values-" + targetlang
    shutil.rmtree(outputfolder,ignore_errors=True)
    os.mkdir(outputfolder)
    outputfile = outputfolder + "/strings.xml"

    tree = ET.parse(sourcedoc)
    root = tree.getroot()
    for rank in root.iter('string'):
        if(rank.attrib["name"].startswith("uistr_")): # todo
            new_rank = translate(rank.text,targetlang)
            print("updating ",rank.text," to ",new_rank)
            rank.text = new_rank
            rank.set('updated', 'yes')

    tree.write(outputfile, method="xml")

def worker():
    while True:
        lang = q.get()
        translate_file(lang["language"])
        q.task_done()

def run_quickstart():
    import threading
    threads = []
    for i in range(threadcount):
        t = threading.Thread(target=worker)
        threads.append(t)
        t.start()

    for lang in get_languages():
        q.put(lang)
    q.join()

if __name__ == '__main__':
    run_quickstart()


```
