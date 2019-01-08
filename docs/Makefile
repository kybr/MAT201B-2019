.SUFFIXES:

_: index.html assignments.html setup.html syllabus.html

%.html: %.md tufte.html5 $(STYLES)
	pandoc \
		--filter pandoc-sidenote \
		--filter pandoc-crossref \
		--filter pandoc-citeproc \
		--katex \
		--section-divs \
		--from markdown+tex_math_single_backslash \
		--to html5+smart \
		--template=tufte \
		--css latex.css \
		--css pandoc-solarized.css \
		--css pandoc.css \
		--css tufte-extra.css \
		--css tufte.css \
		--output $@ \
		$<

clean:
	rm *.html
