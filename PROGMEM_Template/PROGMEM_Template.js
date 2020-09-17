const io = require('console-read-write');
let strings = [];

async function main() {
    while(true)
    {
        io.write('Please enter name of array');
        let name = (await io.read()).trim().replace(' ', '_');

        io.write('Please paste c++ intializer');
        let orginalInitializer = await io.read();
        strings = JSON.parse(orginalInitializer.replace('{', '[').replace('}',']'));
        
        let mainArrayStr = "";

        io.write('Copy this...');
        io.write('');
        io.write(`// ${orginalInitializer}`);
        for(let i = 0; i < strings.length; i++){
            //const char S_Demo[] PROGMEM = "Demo";
            io.write(`const char S_${strings[i].split(' ').join('_')}[] PROGMEM = "${strings[i]}";`)
            mainArrayStr += `, S_${strings[i].split(' ').join('_')}`;
        }
        mainArrayStr = mainArrayStr.substring(2);
        io.write('');
        io.write(`const char *const ${name}[] PROGMEM = {${mainArrayStr}};`);
        io.write(`const byte numOf${name.charAt(0).toUpperCase() + name.slice(1)} = ${strings.length};\n`);
        
        io.write('Enter anything to continue')
        if(await io.read() == '')
            break;
    }       
}

main();

