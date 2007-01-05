$Id: README.txt,v 1.2 2005/11/10 09:36:32 crunchywelch Exp $

Flexinode is a module that allows non-programmers to create new node
types (flexible content types) in Drupal when their needs are modest.
Users can define the fields in the node edit form for their content type,
and can either view the nodes as presented by the module or modify the
presentation in their theme.


Installation

Import the database tables and enable the module. See the INSTALL file.


Editing Content Types

The administration pages for this module are located at:
Administration -> Content Management, on the Content Types tab
Click on the "add content type" tab to make a new one. On this page you can set
the title of your new content type and some related information.

Once you save your new type, you can add new custom fields to it using
the links on the overview page. You can add a variety of fields.
The Title and Description fields are always shown.


Viewing Content

Adding flexible content is just like adding other nodes; pick the
appropriate link from the user menu. The node will show up alongside
all normal nodes.


Theming Content

Every custom field is set as a property of the node. To create a custom
presentation for your new content type, add logic in your theme's node
function to switch on the node type and print out the fields in the
way you choose. The fields are all named flexinode_n where n is the
field ID.

Alternately, you can override the theme_flexinode_* functions to change
the look of all fields of a certain type.