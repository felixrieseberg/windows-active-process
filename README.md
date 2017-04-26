## windows-active-process
Quickly check which app is currently in the foreground. Returns the full path.

```
npm install windows-active-process
```

```
const { getActiveProcessName } = require('windows-active-process')
const activeProcess = getActiveProcessName()

// For instance 'C:\Users\felixr\AppData\Local\hyper\app-1.3.1\Hyper.exe'
```

#### License
MIT, please see LICENSE for details. Copyright (c) 2017 Felix Rieseberg.
