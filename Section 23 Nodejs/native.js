const { isUtf8 } = require("buffer");
const fs = require("fs");

// fs.writeFile("message.txt" , "Heyy My name is Vaidik " , (err) => {
//     if (err) throw err;
//     console.log('The file has been saved!');
//   }); 

  fs.readFile("./message.txt",'utf8' ,(err, data) => {
    if (err) {
      console.error(err);
      return;
    }
    console.log(data);
  });

  