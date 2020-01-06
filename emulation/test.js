
const computer = () => {

    this.stack = '';
    this.halt = false;

    this.main = () => {
        console.log(this.stack);
    }

    this.setup = () => {
        console.log('setup');
    }

    return this;
}


//Emulate clock 
let instance1 = computer();

instance1.setup();
setInterval(() => {
    if(!instance1.halt) instance1.main();
}, 100);

//Captures users input
const inputCapture = () => {      
    
    process.stdin.setEncoding('utf-8');
    
    process.stdin.on('data', (data) => {
        if(data === 'exit\n'){
            open(); 
            process.exit(); 
        }

        instance1.stack += data.trim();
    });
}


inputCapture();