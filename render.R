# render.R
# This script initializes the rendering process of the markdown document

# Set encoding
Sys.setlocale("LC_ALL", "en_US.UTF-8")

# Render markdown document
rmarkdown::render("markdown.Rmd", "all", encoding="UTF-8")
