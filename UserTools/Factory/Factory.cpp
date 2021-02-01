#include "Factory.h"

ToolSelect.sh Factory(std::string tool) {
ToolSelect.sh ret=0;

// if (tool=="Type") tool=new Type;
if (tool=="Poll") ret=new Poll;
if (tool=="Recieve") ret=new Recieve;
if (tool=="Set") ret=new Set;
if (tool=="Stream") ret=new Stream;
  if (tool=="Emergency") ret=new Emergency;
return ret;
}
