{
  "targets": [
    {
      "target_name": "processname",
      "sources": [ "lib/processname.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
