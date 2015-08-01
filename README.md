# QRODS
QRODS -  A Qt library for iRODS data system direct access

QRODS is a library that enables software engineers to build Qt graphical user interfaces (GUI) which can access
the iRODS storage platform. The current version of QRODS implements essential manipulation functionalities
of files and directories (collections) including metadata object information. Therefore, the QRODS may perform
the following proceedings:
• Download, upload and delete files;
• Create and delete collections;
• Add and delete metadata from an object;
• List content (files, metadata, collections) and
• Lazy loading (collection and files - no metadata).

In order to be able to perform any of the above functionalities, QRODS users must instantiate a QRODS
object. After that, it is possible to call each specific method to conduct those operations.

# RODs EXplorer - RODEX

RODs EXplorer (RODEX) is a common Qt framework application built to show the main functionalities of QRODS library.
Such application is able to upload and download files, create and delete files or collections. It
also allows one to add, delete and list file metadata, and to list content (files, metadata or collections) of iRODS
data system. In order to add such functionalities to the Qt framework, Qt developers just need to include QRODS
library into their project.

For a complete knowledge about QRODS (and RODEX), please download the QRODS User Manual.

