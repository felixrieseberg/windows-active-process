const addon = require('bindings')('processname')

/**
 * Get's the active process in the foreground. If the native call
 * fails, it'll return an empty string.
 *
 * @returns {string} Path to the active process
 */
function getActiveProcessName() {
  if (process.platform !== 'win32') {
    throw new Error('windows-active-process only works on Windows')
  }

  return addon.getActiveProcessName()
}

module.exports = {
  getActiveProcessName: getActiveProcessName
}
