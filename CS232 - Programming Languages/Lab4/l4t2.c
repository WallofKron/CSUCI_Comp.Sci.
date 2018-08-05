/*
 
 Compile with: gcc -o l4t2 l4t2.c -I/usr/include/libxml2 -lxslt -lxml2
 
 */

#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>


void error(const char *msg)
{
   fprintf(stderr, "ERROR: %s\n", msg);
   exit(1);
}

int is_valid(const xmlDocPtr doc, const char *schema_filename)
{
   xmlDocPtr schema_doc = xmlReadFile(schema_filename, NULL, XML_PARSE_NONET);
   if (schema_doc == NULL) {
      error("Failed to load XML schema.");
   }
   
   xmlSchemaParserCtxtPtr parser_ctxt = xmlSchemaNewDocParserCtxt(schema_doc);
   if (parser_ctxt == NULL) {
      error("Failed to create parsing context.");
   }
   
   xmlSchemaPtr schema = xmlSchemaParse(parser_ctxt);
   if (schema == NULL) {
      error("XML Schema in invalid.");
   }
   
   xmlSchemaValidCtxtPtr valid_ctxt = xmlSchemaNewValidCtxt(schema);
   if (valid_ctxt == NULL) {
      error("Failed to create validation context.");
   }
   
   int is_valid = (xmlSchemaValidateDoc(valid_ctxt, doc) == 0);
   
   xmlSchemaFreeValidCtxt(valid_ctxt);
   xmlSchemaFree(schema);
   xmlSchemaFreeParserCtxt(parser_ctxt);
   xmlFreeDoc(schema_doc);
   
   return is_valid;
}

void print_catalog(xmlDocPtr doc)
{
   xmlNode *root_node = xmlDocGetRootElement(doc);
    xmlNode        *root, *first_child, *node;
    
    
    fprintf(stdout, "Root is <%s> (%i)\n", root_node->name, root_node->type);
    first_child = root_node->children;
    for (node = first_child; node; node = node->next) {
        fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
    }
    fprintf(stdout, "...\n");
    
    
    
    
}
int main(int argc, char **argv){
   (void) argc;
   (void) argv;
   
   if (argc < 3)
   {
      printf("Usage: l11q1 <xml file> <schema file>\n");
      exit(1);
   }
   

   printf("Loading %s\n", argv[1]);
   xmlDocPtr doc = xmlReadFile(argv[1], NULL, XML_PARSE_NONET | XML_PARSE_NOBLANKS);
   if (doc == NULL) {
      error("Failed to load.");
   }
   printf("Loaded.\n");
   
   printf("Validating with %s\n", argv[2]);
    
   if (!is_valid(doc, argv[2])) {
      error("Failed to validate.");
   }
    
   printf("Validated.\n");
   
   print_catalog(doc);
   
   xmlFreeDoc(doc);
   
   return 0;
}
