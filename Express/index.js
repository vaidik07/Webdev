import express from "express";
const app = express();
var port =3000;

app.get("/" , (req , res )=>{
    console.log(req.rawHeaders);
    res.send("Hello world");
});

app.get("/about" , (req , res )=>{
    res.send("<h1>My name is vaidk parashar</h1>");
});

app.get("/contact" , (req , res )=>{
    res.send("<h1>My phone is 394893<h1>");
});

app.listen(port , ()=>{
    console.log("App is running on " + port);
});
