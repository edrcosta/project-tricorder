/**
 * Javascript terminal Brain fuck emulator 
 * 
 * this code will be ported to C++ to run inside a atmega with a oled display 
 * 
 * chalk and clear modules will be replaced by uglib2
 * 
 */

const chalk = require('chalk');
const clear = require('clear');

let gui = true;
let M = Array(32).fill(0);
let P = 0;
let instructionStack = '';
let instructionStackLoop = '';
let keyboardCheck = 0;
let fechedInst = '';
let updateScreen = true;
let cumulativeOutput = true;
let systemOutput = '';
let isLoop = false;
let instruction = {};
let clockSpeed = 0.000125;

instruction['>'] = () => P++;
instruction['<'] = () => P--;
instruction['-'] = () => M[P]--;
instruction['+'] = () => M[P]++;
instruction['c'] = () => systemOutput = '';

instruction['['] = () => {
    isLoop = true;
};

instruction[']'] = () => {
    if(isLoop){
        instructionStack += instructionStackLoop.trim();
    }
    isLoop = false;
};

const setup = () => {

}

const screenUpdate = () => {

    if (!gui) return false;

    clear();

    console.log(chalk.yellow('========== Terminal Brainfuck emulator =========='));
    console.log(chalk.blue(M.join(' ')));

    const pointerChar = ((p) => `↑${chalk.underline(chalk.red(p))}`)(P);

    let render = M.map((mm, i) =>  i === P ? (P === 0 ? pointerChar : pointerChar) : `  `);

    console.log(render.join('') + '\n' + systemOutput);
    console.log(instructionStackLoop);
}

const fecthAndExec = () => {

    fechedInst = instructionStack.slice(0, 1);

    const removed = instructionStack.substr(1);
    
    instructionStack = removed; 
    
    if(isLoop && removed !== ']'){
        instructionStackLoop = instructionStackLoop.trim() + removed; 
    }
}

const main = () => {

    if( keyboardCheck != instructionStack.length){

        keyboardCheck = instructionStack.length;
    
        fecthAndExec();
    
        if(instructionStack.length === 0) return false;
        if(updateScreen) screenUpdate(); 
    
        if(typeof instruction[fechedInst] === 'function'){
            instruction[fechedInst]();
        }else if(fechedInst.trim().length > 0){
            if(cumulativeOutput){
                systemOutput += '\nUnknow instruction !!! ' + fechedInst;
            }else{
                systemOutput = 'Unknow instruction !!! ' + fechedInst;
            }
        }
    }
}
screenUpdate(); 
setInterval(main, clockSpeed);

process.stdin.setEncoding('utf-8');
process.stdin.on('data', (code) => {
    if(code === 'exit\n'){
            //we have to go out some time
        open(); process.exit(); 
    }

    instructionStack += code;
});