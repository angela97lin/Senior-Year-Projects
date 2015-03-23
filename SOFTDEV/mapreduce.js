/* Map, filter, reduce
Map: maps an array onto another array without the use of for-loops each time
--> it is possible to map an mapped array



Filter: uses a check in order to filter the data so we are left with just the data we are interested in


Lazy Evaluation: waits until the program needs information to evaluate, and remembers where it was before:

for example, in the Linux terminal: cat f | tr a-z A-Z | grep A | wc
In this example, all four commands are run at the same time

filter(map(map(s, f1), f2), f3) --> in full-blownness, would be more efficient than separating because data is only read once

Built in fxns:

map: works on arrays; [1,2,3].map(function (x){return x+x}) --> [1, 4, 9]

So in our dataset: scores.map(f1).map(f2).filter(f3)

--> Built in functions may or may not run in different browsers, since map/filter/reduce are rather new. Also, the built-in fxns ONLY work for arrays, not dictionaries or other objects 

Prototypical inheritance:
.proto: strings, array length, etc.


So we will use third-party sources:
_.reduceRight: reduces from right to left
_.map
_.reduce
_.filter
_.max
_.every (true if data is true for all data)
_.some
_.pluck(scores, "math")
Will use built-in if possible, else, will use Underscore's version
uses .map(data, fxn ~~~)

r = _.chain(scores)
    _.pluck("math")
    _.map(function(x) { return parseInt(x); }
    _.value();

--> last arg must be .values()

We will use lodash:
-->partial evaluation and currying?
uses lazy evaluation
faster, more robust

functional.js
score_.js




-----------------------------------------------------------------------------
l = $("li")
l.map(function(x){ console.log(x) }

========================================================================
2/26/2015

Lisp Macros: used to change code at runtime

Currying / Partial Application:

Needing (x,y,z) -->
if you first only give an x, it will return a fxn that waits for only a y and z later

var add2 = function(a, b){
    return a + b;
}
var add2 = _.curry(function(a, b){
    return a + b;
});


var add2 = function(a){
    return function(b){
	return a+b;
    }
}

plus10 = add2(10)
plus10(15) ==> 25



var add3 = function(a, b, c){
    return a + b + c;
}

*/

var add2 = _.curry(function(a, b){
    return a + b;
});


cmap = .curry(_.map, 2);//cmap takes data and fxn

x= cmap(scores); //waits for last value

x(function(x){return x.math});//fills in second value


var cmap = .curryRight(_.map, 2);
var cfilter = _.curryRight(_.filter, 2);
var cpluck = _.curryRight(_.pluck, 2);

//convert --> list of fxns
convert = _.compose(
    cfilter(function(x){ return !isNan(x); }),
    cpluck("math"),
    cfilter(function(x){ return parseInt(x.num)>800; })
);

_.each(l, function(item, index, list) { console.log(item, index, list);})

_.map(l, function(item, index) { if (index%2 == 0) return item; else return item+00; })


//arguments is similar to *args
var printargs = function(){
    console.log(arguments);
}

mtn = [20, 30, 33, 40, 50, 40, 20, 70, 50, 10, 45]
_zip([1,2,3], [10, 20, 30])

//zip returns tuples
var difflist = zip(mtns, mtns.slice(1));
//difflist = difflist.slice(1, difflist.length-1);
difflist = _.take(difflist, difflist.length-1);
//you can't use slice in chain --> using take 

diffs = _.map(difflist, function(item){
    return Math.abs(item[1] - item[0]);
});

bigdiffs = _.filter(diffs, function(item) {
    return item >= 30;
});


//zip does not work in chain
var difflist = _.zip(mtns, mtns.slice(1));
bigdiffs = _.chain(difflist)
    .take(difflist.length-1)
    .map(function(item){return Math.abs(item[1]-item[0]);}
	 .filter(function(item){return item>=30;})
	 .values();


l = [];
for (i=0; i<20; i++){
    l.push(Math.floor(Math.random()*100));
}

var qsort = function(l){
    if (l.length <= 1){ //base case
	return l;
    }
    //typical pivot is median of l[0], l[l.length-1], and l[mid]
    var pivot = l[0];
    l = l.slice(1);
    /*
      var lower = _.filter(l, function(x){
      return x <= pivot;
      }); //gives all items lower than pivot
      var upper = _.filter(l, function(x){
	   return x > pivot;
	   }); //gives all items greater than pivot
    */
    var p = _.partition(l, function(x){ return x<=pivot; });
    //partition splits into two arrays
    return qsort(p[0]).concat(pivot).concat(qsort(p[1]));
};
		 /*
QUICK SORT
Best case: nlog(n)
Worst case: n^2
[3, 2, 8, 4, 7, 9, 6, 5]
Choose pivot: 4
Then move everything greater to the right, move everything less than to the left*/
