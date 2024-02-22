for(var i=0 ; i<document.querySelectorAll("button").length ; i++)
{
document.querySelectorAll("button")[i].addEventListener("click" , function()
{
    var buttonInnerHTML = this.innerHTML;
    makeSound(buttonInnerHTML);
    buttonAnimation(buttonInnerHTML);
}
);
}

document.addEventListener("keypress" , function(event){
    makeSound(event.key);
    buttonAnimation(event.key);
});

function makeSound(key){
    if(key=='s')
    {
        var audio = new Audio("sounds/tom-1.mp3");
        audio.play();
    }
    if(key=='d')
    {
        var audio = new Audio("sounds/tom-2.mp3");
        audio.play();
    }
    if(key=='j')
    {
        var audio = new Audio("sounds/tom-3.mp3");
        audio.play();
    }
    if(key=='k')
    {
        var audio = new Audio("sounds/tom-4.mp3");
        audio.play();
    }
    if(key=='l')
    {
        var audio = new Audio("sounds/crash.mp3");
        audio.play();
    }
    if(key=='w')
    {
        var audio = new Audio("sounds/kick-bass.mp3");
        audio.play();a
    }
    if(key=='a')
    {
        var audio = new Audio("sounds/snare.mp3");
        audio.play();
    }
    //switch statement can also be used

}

function buttonAnimation(currentKey)
{
    var activeButton = document.querySelector("." + currentKey);

    activeButton.classList.add("pressed");
    setTimeout(function(){
        activeButton.classList.remove("pressed");

    },.500)
}


