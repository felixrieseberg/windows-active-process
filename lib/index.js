const addon = require('bindings')('processname')

module.exports = {
  getActiveProcessName: addon.getActiveProcessName
}
