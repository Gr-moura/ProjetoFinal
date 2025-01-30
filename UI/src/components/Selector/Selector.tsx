import "./Selector.css";
import { useState } from "react";


/**
 * @interface SelectorProps
 * @brief Propriedades do componente Selector.
 * @property {Array<{name: string, value: number, index: number}>} items Itens disponíveis para seleção.
 * @property {(arg0: number) => void} setAction Função chamada ao selecionar um item.
 */
interface SelectorProps{
    items:{name:string, value:number, index:number}[]
    setAction:(arg0:number)=>void;
}


/**
 * @brief Componente que permite a seleção de um item em uma lista.
 * @param {SelectorProps} props Propriedades do componente.
 * @return {JSX.Element} Retorna o componente de seleção.
 */
export const Selector = ({items, setAction}:SelectorProps) => {
    const [selectedItem, setSelectedItem] = useState(items[0])

    /**
     * @brief Move "steps" posições em um array a partir de uma posição inicial.
     * @param {Array<any>} array Array no qual a movimentação será realizada.
     * @param {number} beggining Posição inicial no array.
     * @param {number} steps Número de posições a serem percorridas.
     * @return {number} Retorna a posição final após a movimentação.
     */
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

    /**
     * @brief Navega pelos itens disponíveis e atualiza o item selecionado.
     * @param {number} step Número de posições a serem percorridas (positivo para frente, negativo para trás).
     */
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