import "./Selector.css";
import { useEffect, useState } from "react";

interface SelectorProps{
    items:{name:string, value:number, index:number}[]
    setAction:(arg0:number)=>void;
}

export const Selector = ({items, setAction}:SelectorProps) => {
    const [selectedItem, setSelectedItem] = useState(items[0])

    //moves "steps" positions in an array relative to "beginning" position
    const walkInArray = (array:any[], beggining:number, steps:number)=>{
        let endPosition = beggining+steps;
        while(endPosition<0 || endPosition>=array.length){
            if(endPosition<0){
                endPosition = endPosition + array.length;
            }
            if(endPosition>=array.length){
                endPosition = endPosition - array.length;
            }
        }
        return endPosition;
    }

    //uses walkInArray to select next or previous item
    const walkThroughItems = (step:number) => {
        let updatedItem = items[walkInArray(items, selectedItem.index, step)];
        setSelectedItem(updatedItem);
        setAction(updatedItem.value);
    }

    return(
        <div className="selectorbody">
            <div className="clickablediv" onClick={()=>walkThroughItems(-1)}>
                <a className="clickabletext">{"<"}</a>
            </div>
            <a className="nametext">{selectedItem.name}</a>
            <div className="clickablediv" onClick={()=>walkThroughItems(+1)}>
                <a className="clickabletext">{">"}</a>
            </div>
        </div>
    )
}