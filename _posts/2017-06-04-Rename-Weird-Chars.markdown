---
layout: post
title: Türkçe Karakter Problemi
author: Yunus Emre AYHAN
date:   2017-06-04 15:42:00
categories: Python
comments: true
---

Bu yazımda türkçe karakterlerden dolayı yaşadığım bir sıkıntıyla ilgili yazdığım bir scripti paylaşmak istiyorum. İhtiyaç duyulabilecek birşey.

# Türkçe Karakter Problemi

Linux kullanıcısı olarak genelde bütün programlar, diğer karakterlerin kullanımını göz önünde bulundurmayabiliyor. Elimde mesela bir ebup arşivi vardı, sıkıştırma programından kaynaklı olduğunu zannediyorum, dosya isimlerin deki esrarengiz karakterlerden muzdaripdim('ƒ', '±', '√', '∂', 'ß', '≈', 'ü',
'º', 'ñ', '∞', 'á', 'û', 'ö', 'ú', 'ª', '¢').  Bu karakterlerden dolayı, dosyalarım evdeki home serverda bulunduğu için, dosyalara erişim de sağlayamıyordum. Çare python deyip ufak bir script yazdım. Şuan ki haliyle script bu tuhaf karakterleri ingilizce karşılıklarına çeviriyor. Yazmışken türkçe karakterleri ingilizce karakterlere çeviren fonksiyonuda ekledim. Neyse uzatmayayım script biraz karışık gibi ama fonksiyonlardan ne yaptığı zannediyorum anlaşılır. Düzenlenip kullanılabilir. Çalıştırmak için isim değişikliği yapmasını istediğimiz klasörü girdi olarak veriyoruz :

> python myscript.py "dir_to_convert"

### KOD :

```python
#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import os

dir = sys.argv[1]

logfile = open("renamefile.log", "w")

turkish_chars_then = ["√∂", "ƒ±", "√ß", "≈ü", "ƒü", "√º",
                      "√ñ", "ƒ∞", "Ç", "≈û", "√ö", "√ú", "√ª", "√¢", "√Æ"]
turkish_chars = ['ö',  'ı', 'ç', 'ş', 'ğ', 'ü', 'Ö',
                 'İ', 'Ç', 'Ş', 'Ğ', 'Ü', 'û', 'a', "i"]
turkish_chars_code = [154,  221, 141, 223, 219, 159,
                      133, 220, 130, 222, 218, 134, 251, 97,  105]
eng_chars = ['o',  'i', 'c', 's', 'g', 'u', 'O',
             'I', 'C', 'S', 'G', 'U', 'u', 'a', "i"]
eng_chars_code = [111,  105,  99, 115, 103, 117,
                  79,  73,  67,  83,  71,  85, 117, 97,  105]

weirdcharsselfs = ["ƒ", "±", "√", '∂', 'ß', '≈', 'ü',
                   'º', 'ñ', '∞', 'á', 'û', 'ö', 'ú', 'ª', '¢', 'Æ']
weirdcharscodes = [196, 177, 195, 182, 167, 197, 159,
                   188, 150, 176, 135, 158, 154, 156, 187, 162, 198]
weirdchar_patterns = [[195, 182], [196, 177], [195, 167], [197, 159], [196, 159], [195, 188], [195, 150], [
    196, 176], [195, 135], [197, 158], [195, 154], [195, 156], [195, 187], [195, 162], [195, 198]]


def prnt_ascii_values():
    for i in range(256):
        print(chr(i) + " > " + str(i))


def isWeirdChar(c):
    for weirdcharcode in weirdcharscodes:
        if(ord(c) == weirdcharcode):
            return True
    return False


def isTurkishChar(c):
    idx = -1
    for c in turkish:
        if(ord(c) == weirdcharcode):
            return idx
        idx = idx + 1
    return idx


def rename(name, convert_name, root):
    '''This function makes renaming with proper logs  '''
    logfile.write("\n renaming file : " + name + "   to : " + convert_name)
    src = os.path.join(root, name)
    dst = os.path.join(root, convert_name)
    logfile.write("\n rename source : " + src)
    logfile.write("\n rename destination : " + dst)
    try:
        os.rename(src, dst)
    except Exception:
        print("os rename error for : " + src)
        logfile.write("----> fail rename source : " + src)


def weirdCharPatternMatch(check):
    idx = 0
    for wc_pattern in weirdchar_patterns:
        if(check == wc_pattern):
            return idx
        idx = idx + 1
    return -1


def convertWeirdCharsToIngChars(name):
    resname = str("")
    prev_weird_char = " "
    cur_weird_char = " "
    for c in name:
        if(isWeirdChar(c)):
            prev_weird_char = cur_weird_char
            cur_weird_char = c
            res = weirdCharPatternMatch(
                [ord(prev_weird_char), ord(cur_weird_char)])
            if(res != -1):
                resname += chr(eng_chars_code[res])
        else:
            resname += c
    return resname


def convertTurkishCharsToIngChars(name):
    resname = str("")
    for c in name:
        res = isTurkishChar(c)
        if(res != -1):
            resname += chr(eng_chars_code[res])
        else:
            resname += c
    return resname


def convertTurkishCharsInDir():
    for root, dirs, files in os.walk(toconv):
        for name in files:
            newname = convertTurkishCharsToIngChars(name)
            if(name != newname):
                rename(name, newname, root)
        for dname in dirs:
            newname = convertTurkishCharsToIngChars(dname)
            if(dname != newname):
                rename(dname, newname, root)


def convertWeirdCharsInDir(toconv):
    for root, dirs, files in os.walk(toconv):
        for name in files:
            newname = convertWeirdCharsToIngChars(name)
            if(name != newname):
                rename(name, newname, root)
        for dname in dirs:
            newname = convertWeirdCharsToIngChars(dname)
            if(dname != newname):
                rename(dname, newname, root)


convertWeirdCharsInDir(dir)
logfile.close()

```
