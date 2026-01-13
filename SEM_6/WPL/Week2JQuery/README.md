# jQuery

jQuery is a fast and concise JavaScript library to develop web based application.

Core features supported by jQuery −
- DOM manipulation − easy to select DOM elements, negotiate them and modifying their content by using cross-browser open source selector engine called Sizzle.
- Event handling − offers an elegant way to capture a wide variety of events, such as a user clicking on a link, without the need to clutter the HTML code itself with event handlers.
- AJAX Support − eases developing a responsive and feature rich site using AJAX technology.
- Animations − plenty of built-in animation effects which you can use in your websites.
- Lightweight − very lightweight library - about 19KB in size (Minified and gzipped).
- Cross Browser Support − works in IE 6.0+, FF 2.0+, Safari 3.0+, Chrome and Opera 9.0+
- Latest Technology − CSS3 selectors and basic XPath syntax.

## Selector: 

Technique for selecting and working on a collection of elements—CSS selectors. The basic syntax is like this:
$('selector') use a CSS class
selector like this:
$('.submenu')

## Events
To make your web page interactive, you write programs that respond to events.
- Mouse events: click, dblclick, mousedown, mouseup, mouseover, etc
- Document/Window Events: load, resize, scroll, unload etc
- Form Events: submit, reset, focus, and change

- The bind() method is a more flexible way of dealing with events than jQuery’s event
specific functions like click() or mouseover(). It not only lets you specify an event and a function to respond to the event, but also lets you pass additional data for the event-
handling function to use.
```
$('#theElement').bind('click', function() {
// do something interesting
}); // end bind
```
- each() 
Used to execute a function for each matched element.

## animate() Method
The jQuery animate() method is used to create custom animations.
```
$(selector).animate({params},speed,callback);
```
The required params parameter defines the CSS properties to be animated.
The optional speed parameter specifies the duration of the effect. It can take the following
values: "slow", "fast", or milliseconds.
The optional callback parameter is a function to be executed after the animation completes.
```
$("button").click(function(){
$("div").animate({left:'250px'});
});
```
