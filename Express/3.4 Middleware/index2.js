import express from "express";
import bodyParser from "body-parser";
import morgan from "morgan";


const app = express();
app.use(morgan("tiny"));

const port = 3000;

app.use(bodyParser.urlencoded({extended: true}));


app.get("/", (req, res) => {
  res.send("Hello");
});

app.listen(port, () => {
  console.log(`Listening on port ${port}`);
});
