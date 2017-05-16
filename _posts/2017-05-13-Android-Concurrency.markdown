---
layout: post
title: Concurrency in Android
author: Yunus Emre AYHAN
date:   2015-04-09 11:23:32
categories: Android
comments: true
---

In some cases, for some reason developer may need to do something in background(like server operations). In those cases doing the stuff in the main ui thread will consume time and make the application seem bulky. To figure out those tasks android offer simple solutions like async and handler. Both async and handler uses threads to handle their job in the background. But they provide solution on simple tasks, to the basic thread problems, like :

* Synchronization with the main thread if you post back results to the user interface
* No default for canceling the thread
* No default thread pooling
* No default for handling configuration changes in Android

---

### Using Threads

### Using Handler Class


### Using Async Class

AsyncTask enables proper and easy use of the UI thread. This class allows to perform background operations and publish results on the UI thread without having to manipulate threads and/or handlers.

Async class, gets three types in construction. It is like Async\<params, update, result>. There are three important functions also may be overriden in this class using those three types : doInBackground, onPostExecute, onProgressUpdate. To pass progress value to the onProgressUpdate we need the use publishProgress function. The possible reason to use onPostExecute and onProgressUpdate is we may need to update some ui element which run on generic ui thread. Which we can not manipulate at doInBackground task. Because a ui element can only be manipulated from same thread it runs on.

```java
new AsyncTask<Void, Void, String>() {
    @Override
    protected String doInBackground(Void... voids) {
        String ret = someServerStuff("username", "password",
        	"ipaddr", portno);
        return ret;
    }

    @Override
    protected void onPostExecute(String s) {
        super.onPostExecute(s);
        TextView tv2 = (TextView)
        	findViewById(R.id.sample_text);
        tv2.setText(s);
	}

    @Override
    protected void onProgressUpdate(Void... values) {
        super.onProgressUpdate(values);
    }
}.execute();
```
