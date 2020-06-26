# render.R

# Set encoding and render markdown file
Sys.setlocale("LC_ALL", "en_US.UTF-8")
rmarkdown::render("markdown.Rmd", "all", encoding="UTF-8")
