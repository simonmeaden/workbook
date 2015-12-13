
TEMPLATE = subdirs

SUBDIRS += \
    workbooklib \
    plugin \
    examples

plugin.subdir = plugin

workbooklib.subdir = workbooklib
workbooklib.depends += plugin

examples.subdir = examples
examples.depends += workbooklib

