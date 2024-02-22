function sum(a,b){
    const sum = a+b;
    console.log(sum);
    return sum;
}

const square = function(a){
    return a*a;
}

let a =10;
let b=20;
//console.log(a+b);
const result = sum(a,b);
console.log(result);
console.log(square(3));

const words = ["apple" , "banna" , 12 , true];
words.push("vaidik");

//in js array can take mixed data types like objects functions bool
console.log(words);