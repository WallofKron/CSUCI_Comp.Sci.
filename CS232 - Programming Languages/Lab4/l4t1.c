#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlschemas.h>
int pos=0;

xmlParserInputPtr resolveEntity(void *user_data, const xmlChar *publicId, const xmlChar *systemId)
{
    // printf("resolveEntity(publicId='%s', systemId='%s')\n", publicId, systemId);
    fflush(stdout);
    return NULL;
}

void internalSubset(void *user_data, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID)
{
    //("internalSubset(name='%s', ExternalID='%s', SystemID='%s')\n", name, ExternalID, SystemID);
    fflush(stdout);
}

void externalSubset(void *user_data, const xmlChar *name, const xmlChar *ExternalID, const xmlChar *SystemID)
{
    // printf("externalSubset(name='%s', ExternalID='%s', SystemID='%s')\n", name, ExternalID, SystemID);
    fflush(stdout);
}

xmlEntityPtr getEntity(void *user_data, const xmlChar *name)
{
    // printf("getEntity(name='%s')\n", name);
    fflush(stdout);
    return NULL;
}

xmlEntityPtr getParameterEntity(void *user_data, const xmlChar *name)
{
    // printf("getParameterEntity(name='%s')\n", name);
    fflush(stdout);
    return NULL;
}

void entityDecl(void *user_data, const xmlChar *name, int type, const xmlChar *publicId, const xmlChar *systemId, xmlChar *content)
{
    // printf("entityDecl(name='%s', type=%i, publicId='%s', systemId='%s', content='%s')\n", name, type, publicId, systemId, content);
    fflush(stdout);
}

void notationDecl(void *user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId)
{
    // printf("notationDecl(name='%s', publicId='%s', systemId='%s')\n", name, publicId, systemId);
    fflush(stdout);
}

void attributeDecl(void *user_data, const xmlChar *elem, const xmlChar *fullname, int type, int def, const xmlChar *defaultValue, xmlEnumerationPtr tree)
{
    (void)tree;
    // printf("attributeDecl(elem='%s', fullname='%s', type=%i, def=%i, defaultValue='%s')\n", elem, fullname, type, def, defaultValue);
    fflush(stdout);
}

void elementDecl(void *user_data, const xmlChar *name, int type, xmlElementContentPtr content)
{
    (void)content;
    // printf("elementDecl(name='%s', type=%i)\n", name, type);
    fflush(stdout);
}

void unparsedEntityDecl(void *user_data, const xmlChar *name, const xmlChar *publicId, const xmlChar *systemId, const xmlChar *notationName)
{
    // printf("unparsedEntityDecl(name='%s', publicId='%s', systemId='%s', notationName='%s')\n", name, publicId, systemId, notationName);
    fflush(stdout);
}

void setDocumentLocator(void *user_data, xmlSAXLocatorPtr loc)
{
    (void)loc;
    // printf("setDocumentLocator()\n");
    fflush(stdout);
}

void startDocument(void *user_data)
{
   // printf("startDocument()\n");
    fflush(stdout);
}

void endDocument(void *user_data)
{
    //printf("endDocument()\n");
    fflush(stdout);
}

void startElement(void *user_data, const xmlChar *name, const xmlChar **atts)
{
    int choice = 0;
    /*
     
     int i;
     printf("startElement(name='%s', atts=", name);
     fflush(stdout);
     if (atts != NULL) {
     printf("{");
     fflush(stdout);
     for (i = 0; atts[i] != NULL; i++) {
     printf("'%s'", atts[i]);
     fflush(stdout);
     if (atts[i + 1] != NULL) {
     printf(", ");
     }
     }
     printf("}");
     fflush(stdout);
     } else {
     printf("NULL");
     fflush(stdout);
     }
     printf(")\n");
     fflush(stdout);
     
     */
    if (strncmp(name, "catalog", sizeof(name))==0) {
        choice=0;
    }
    
    if (strncmp(name, "year", sizeof(name))==0) {
        choice=1;
    }
    
    if (strncmp(name, "semester", sizeof(name))==0) {
        choice=2;
    }
    
    if (strncmp(name, "mjrprogram", sizeof(name))==0) {
        choice=3;
    }
    
    if (strncmp(name, "Physics", sizeof(name))==0) {
        choice=4;
    }
    
    if (strncmp(name, "classes", sizeof(name))==0) {
        choice=5;
    }
    
    if (strncmp(name, "CMPSCI", sizeof(name))==0) {
        choice=6;
    }

    if (strncmp(name, "Math", sizeof(name))==0) {
        choice=7;
    }
    if (strncmp(name, "description", sizeof(name))==0) {
        choice=8;
    }
    if (strncmp(name, "unitweight", sizeof(name))==0) {
        choice=9;
    }
    if (strncmp(name, "professor", sizeof(name))==0) {
        choice=10;
    }
    if (strncmp(name, "days", sizeof(name))==0) {
        choice=11;
    }
    if (strncmp(name, "time", sizeof(name))==0) {
        choice=12;
    }
    
    
    switch (choice) {
        case 0:
            
            break;
            
        case 1:
            printf("\nYear: %s",atts[1]);
            fflush(stdout);
            break;
            
        case 2:
            printf("\n\n\nSemester: %s\n",atts[1]);
            fflush(stdout);
            break;
            
        case 3:
            printf("Major: ");
            fflush(stdout);
            break;
            
        case 4:
            printf("\n\n\n++Physics: ");
            fflush(stdout);
            break;
            
        case 5:
            if (atts != NULL) {
                printf("\n\nSection: %s\t ",atts[1]);
                fflush(stdout);
            }
            break;
            
        case 6:
            printf("\n\n\n++Comp SCI: ");
            fflush(stdout);
            break;
            
        case 7:
            printf("\n\n\n++Math: ");
            fflush(stdout);
            break;
            
        case 8:
            if (pos==1) {
            printf("Description: %s",atts[1]);
            fflush(stdout);
            }
            break;
            
        case 9:
            printf("\nUnitweight: ");
            fflush(stdout);
            break;
            
        case 10:
            printf("\nProfessor: ");
            fflush(stdout);
            break;
            
        case 11:
            printf("\nDays: ");
            fflush(stdout);
            break;
            
        case 12:
            printf("\nTimes: ");
            fflush(stdout);
            break;
        
        default:
            printf("default");
            fflush(stdout);
            break;
    }
    
    
}

void endElement(void *user_data, const xmlChar *name)
{

}

void attribute(void *user_data, const xmlChar *name, const xmlChar *value)
{
    // printf("attribute(name='%s', value='%s')\n", name, value);
    fflush(stdout);
}

void reference(void *user_data, const xmlChar *name)
{
    // printf("reference(name='%s')\n", name);
    fflush(stdout);
}

void characters(void *user_data, const xmlChar *ch, int len)
{
    char *ptr_ch = (char *) ch;
    while (len-- > 0)
    {
        if (strchr(" \n\t", *ptr_ch) == NULL)
            putchar(*ptr_ch);
        ptr_ch++;
    }
    
    fflush(stdout);
}

void ignorableWhitespace(void *user_data, const xmlChar *ch, int len)
{
    
    char real_ch[len + 1];
    strncpy(real_ch, (char*)ch, len);
    real_ch[len] = 0;
    
    // printf("ignorableWhitespace(ch='%s', len=%i)\n", ch, len);
    fflush(stdout);
}

void processingInstruction(void *user_data, const xmlChar *target, const xmlChar *data)
{
    // printf("processingInstruction(target='%s', data='%s')\n", target, data);
    fflush(stdout);
}

void comment(void *user_data, const xmlChar *value)
{
    // printf("comment(value='%s')\n", value);
    fflush(stdout);
}

void cdataBlock(void *user_data, const xmlChar *value, int len)
{
    printf("cdataBlock(value='%s', len=%i)\n", value, len);
    fflush(stdout);
}

void warning(void *user_data, const char *msg, ...)
{
    printf("warning(msg='%s', ...)\n", msg);
    fflush(stdout);
}

void error(void *user_data, const char *msg, ...)
{
   // printf("error(msg='%s', ...)\n", msg);
    //fflush(stdout);
}

void fatalError(void *user_data, const char *msg, ...)
{
    printf("fatalError(msg='%s', ...)\n", msg);
    fflush(stdout);
}

int isStandalone(void *user_data)
{
    printf("isStandalone()\n");
    fflush(stdout);
    return 1;
}

int hasInternalSubset(void *user_data)
{
    printf("hasInternalSubset()\n");
    fflush(stdout);
    return 1;
}

int hasExternalSubset(void *user_data)
{
    printf("hasExternalSubset()\n");
    fflush(stdout);
    return 1;
}

void startElementNs(void *user_data, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI, int nb_namespaces, const xmlChar **namespaces, int nb_attributes, int nb_defaulted, const xmlChar **attributes)
{
    int i;
    // printf("startElementNs(localname='%s', prefix='%s', URI='%s', nb_namespaces=%i, namespaces={", localname, prefix, URI, nb_namespaces);
    fflush(stdout);
    for (i = 0; i < nb_namespaces; i++) {
        // printf("'%s'", namespaces[i]);
        fflush(stdout);
        if (i + 1 < nb_namespaces) {
            // printf(", ");
        }
    }
    // printf("}, nb_attributes=%i, nb_defaulted=%i, attributes={", nb_attributes, nb_defaulted);
    fflush(stdout);
    for (i = 0; i < nb_attributes; i++) {
        // printf("'%s'", attributes[i]);
        fflush(stdout);
        if (i + 1 < nb_attributes) {
            // printf(", ");
        }
    }
    // printf("})\n");
    fflush(stdout);
}

void endElementNs(void *user_data, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI)
{
    // printf("endElementNs(localname='%s', prefix='%s', URI='%s')\n", localname, prefix, URI);
    fflush(stdout);
}

void serror(void *userData, xmlErrorPtr error)
{
    (void)userData;
    (void)error;
    printf("serror()\n");
    fflush(stdout);
}


xmlSAXHandler saxHandler = {
    .internalSubset =  internalSubset,
    .isStandalone =  isStandalone,
    .hasInternalSubset =  hasInternalSubset,
    .hasExternalSubset =  hasExternalSubset,
    .resolveEntity =  resolveEntity,
    .getEntity =  getEntity,
    .entityDecl =  entityDecl,
    .notationDecl =  notationDecl,
    .attributeDecl =  attributeDecl,
    .elementDecl =  elementDecl,
    .unparsedEntityDecl =  unparsedEntityDecl,
    .setDocumentLocator =  setDocumentLocator,
    .startDocument =  startDocument,
    .endDocument =  endDocument,
    .startElement =  startElement,
    .endElement =  endElement,
    .reference =  reference,
    .characters =  characters,
    .ignorableWhitespace =  ignorableWhitespace,
    .processingInstruction =  processingInstruction,
    .comment =  comment,
    .warning =  warning,
    .error =  error,
    .fatalError =  fatalError,
    .getParameterEntity =  getParameterEntity,
    .cdataBlock =  cdataBlock,
    .externalSubset =  externalSubset,
    .startElementNs =  startElementNs,
    .endElementNs =  endElementNs,
    .serror =  serror,
    .initialized =  1,
};


int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Syntax: %s [document.xml]\n", argv[0]);
        return 1;
    }
    printf("class descriptions on? (1-yes 0-no): ");
    scanf("%d",&pos);
    
    while (pos > 1 || pos < 0) {
        printf("Wrong answer\n");
        printf("\nclass descriptions on? (1-yes 0-no): ");
        scanf("%d",&pos);
    }
    
    
    fprintf(stderr, "Running for: %s\n", argv[1]);
    xmlKeepBlanksDefault(0);
    xmlSAXUserParseFile(&saxHandler, NULL, argv[1]);
    fprintf(stderr, "\n\nDone with: %s\n", argv[1]);
    
    return 0;
}
