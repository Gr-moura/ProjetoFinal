import { useEffect, useState } from "react";
import "./Board.css";
import { useLocation } from "react-router-dom";
import { BoardCell } from "../../components/BoardCell/BoardCell";
import { WinOverlay } from "../../components/WinOverlay/WinOverlay";


interface boardProps{
    height:number,
    widht:number,
    gameName:string
    dificulty:number
    playernames:string[];
}
interface gameEndedType{
        wintype:string;
        winnerplayer:string;
}


export const Board = ()=>{
    const location = useLocation();
    const {height, widht, gameName, dificulty, playernames}:boardProps = location.state || 0;

    const [playerTurn, setPlayerTurn] = useState(1);
    const [clickedCells, setClickedCells] = useState<string[][]>([]);
    const [reset, setReset] = useState(false);
    const [gameEnded, setGameEnded] = useState<gameEndedType>({
        winnerplayer:"none",
        wintype:"none",
    });

    //generating a array to register the clicked cells
    const generateClickArray = () => {
        let newArray:string[][] = [];
        for(let x=0; x<widht; x++){
            newArray.push([]);
            for(let y=0; y<height; y++){
                newArray[x].push("");
            }
        }
        setClickedCells(newArray);
    }

    const checkForEndgame = () => {
        //chekcing to see if there was a tie because the bord is filled
        let boardfilled = true;
        clickedCells.forEach(column => {
            column.forEach(cellclicked => {
                if(cellclicked==""){
                    boardfilled = false;
                }
            })
        });
        if(boardfilled){
            setGameEnded({wintype:"tie", winnerplayer:"none"});
            return;
        } 
    }
    const handleClickedCell = (position:{x:number, y:number}) => {
        //updating board cells
        let updatedClickArray:string[][] = [...clickedCells];
        updatedClickArray[position.x][position.y] = "player"+playerTurn.toString();
        setClickedCells(updatedClickArray);
        //checking if the game ended
        checkForEndgame();
        //changing player turn
        setPlayerTurn(playerTurn==1? 2:1);
    }

    useEffect(()=>{
        setReset(false);
        setPlayerTurn(1);
        setGameEnded({
            winnerplayer:"none",
            wintype:"none"
        })
        generateClickArray();
    }, [reset, widht, length])

    return(
        <div className="boardbody">
            <h1 className="gametitle">{gameName}</h1>
            <h3>turno de {playernames[playerTurn-1]}</h3>
            <ul className="board"> 
                {clickedCells.map((item, index1) => (
                    <ul>
                        {item.map((item, index2)=>(
                            <li>    
                                <BoardCell 
                                    position={{x:index1, y:index2}} 
                                    clickedBy={clickedCells[index1][index2]} 
                                    handleClickedCell={handleClickedCell}
                                />
                            </li>
                        ))}
                    </ul>
                ))}
            </ul>
            <WinOverlay 
                winnerplayer={gameEnded.winnerplayer} 
                wintype={gameEnded.wintype} 
                reset={setReset}
                className={gameEnded.wintype==="none"?"hidden":"show"}
            />
        </div>
    )
}