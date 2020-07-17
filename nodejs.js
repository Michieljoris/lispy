const fs = require('fs');

var str = "";

var memory;
var runtime;

var page_size = 64 * 1024;
var max_page_count = 10;
var max_size = page_size * max_page_count;
var initial_page_count = 2
var page_count = initial_page_count;

// var i8, i16, i32;

var importObject = {
    env: { _putchar: arg => {
        if (arg == 10) { console.log(str); str = ""; }
        else str = str + String.fromCharCode(arg);
        // process.stdout.write(String.fromCharCode(arg))
    },
           grow_memory: () => { console.log("grow_memory");
                                if (++page_count > max_page_count) {
                                    console.log("Error: can't allocate memory beyond max\n");
                                    // throw "Error: can't allocate memory beyond max\n";
                                    return 0;
                                }
                                memory = runtime.memory.grow(1);
                                return 1; },
           get_mem_end:  () => { //console.log("get_mem_end");
               return page_count * page_size},
           // memory:  new WebAssembly.Memory({initial: initial_page_count,
           //                                  maximum: max_page_count})
         }
};

function consoleLogString(memory, offset, length) {
  var bytes = new Uint8Array(memory.buffer, offset, length);
  var string = new TextDecoder('utf8').decode(bytes);
  console.log(string);
}

async function start() {
    try {
        let buf = fs.readFileSync('./out_wasm/runtime.wasm');
        runtime = await WebAssembly.instantiate(new Uint8Array(buf), importObject).
            then(res => res.instance.exports);
        console.log("data_end =", runtime.__data_end.value);
        console.log("calling init_malloc");
        runtime.init_malloc();
        runtime.init_lispy_mempools(800, 800, 800);

        buf = fs.readFileSync('./compiled/lispy.wasm');
        console.log("printf_ :", runtime.printf_);
        // const __data_end = new WebAssembly.Global({value:'i32', mutable:false}, runtime.__data_end);
        let lispyImportObject = { env: { memory: runtime.memory,
                                         printf: runtime.printf_,
                                         init_malloc: runtime.init_malloc,
                                         log: arg => console.log(arg),
                                         __data_end: runtime.__data_end
                                       }};
        let lispy = await WebAssembly.instantiate(new Uint8Array(buf), lispyImportObject).
            then(res => res.instance.exports);

        consoleLogString(lispy.mem, runtime.__data_end.value , 3);
        console.log("test: ", lispy.test);
        lispy.test();
    } catch(e) {
        console.log(e);
    }

}


start();

