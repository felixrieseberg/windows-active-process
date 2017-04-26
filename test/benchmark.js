const perfy = require('perfy')
const getActiveProcessName = require('../lib/index').getActiveProcessName

const iterations = process.argv[2] || 100000

function measureThisTime () {
  perfy.start('this')
  for (let i = 0; i < iterations; i++) {
    getActiveProcessName()
  }

  return perfy.end('this').time
}


// Fight!
console.log(`Reading the active process ${iterations} times:`)

const thisTime = measureThisTime()

console.log(`It took: ${thisTime}`)
