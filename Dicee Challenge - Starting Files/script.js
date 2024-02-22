var dice1 = Math.random();
    dice1=dice1*6+1;
    dice1=Math.floor(dice1);

var dice2 = Math.random();
    dice2=dice2*6+1;
    dice2=Math.floor(dice2);

    var source1 = "images/dice"+dice1+".png";
    var source2 = "images/dice"+dice2+".png";
    document.querySelectorAll("img")[0].setAttribute("src" , source1);;
    
    var image2 = document.querySelectorAll("img")[1];
    image2.setAttribute("src" , source2);

    if(dice1>dice2)
    {
        document.querySelector(".container h1").innerHTML = "Player 1 wins";

    }
    else{
        document.querySelector("h1").innerHTML = "Player 2 wins";

    }