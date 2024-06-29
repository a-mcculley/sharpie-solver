# sharpie-solver
Note (2024): This was originally written in 2020 when I was far less skilled, as a result this code is very sloppy; it solves the problem in a (relatively) clunky way, is certainly not fast, and does not exhibit great style. I would approach the problem differently if I were
to work on it again, and it isn't representative of my current skill level. Additionally, if I recall correctly, when I edited it last I was experimenting with minimizing different parameters and playing around with the code, as a result I may have left it in a broken state 
I do know that it was working at one point though. Additionally, since this was built to solve a specific problem, I was expecting to only run it once, so the inefficiency was more excusable.

Note (2024): The input list containing all of the packs of sharpies is certainly out of date. The prices likely have changed, some colors/themes/packs may be discontinued, new colors or packs have certainly introduced, etc. If you desire to use this, you'd have to update that file.
Good luck though, since sharpies have oddly little documentation; finding a list of colors was very very hard, as was lists of which colors were in each pack or full lists of pack.  

The purpose of this is slightly convoluted; at one point I was interested in trying to get at least one sharpie marker of every color, but I discovered that there wasn't a single package that had them all, nor was there a very logical structure to the packages (for instance, sometimes
one theme's 12 pack may have a color that the theme's 24 pack doesn't). Therefore, I wrote this code in an attempt to figure out what packs I would need to buy; initially I wrote it to minimize the total number of markers (i.e. as few duplicate markers as possible). Then I wrote a version
To minimize the cost, then a version to minimize the number of boxes (in an attempt to minimize hassle). I never did get around to actually buying all of these though.

The list of sharpie packs is currently hard-coded as a file named "sharpie-packs.txt," though it only occurs once in the program, so changing the input name isn't too hard. The format is as follows:
"pack name, cost, num duplicates/markers of a non-standard size, color 1, color 2, color 3". Important to note that each section is separated by ", ". Additionally, each line is the information for exactly one pack.
