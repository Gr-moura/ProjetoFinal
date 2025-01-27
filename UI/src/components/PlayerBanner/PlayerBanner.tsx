import { useState } from "react";
import "./PlayerBanner.css";
import { playerType } from "../../screens/PlayerSelection/PlayerSelection";


interface playerBannerProps extends playerType{
    handleSelectPlayer:(playerNick:string, playerName:string)=>void;
    playerType?:string;
}


export const PlayerBanner = ({playerNick, playerName, score, handleSelectPlayer, playerType}:playerBannerProps) => {
    const [newPlayerName, setNewPlayerName] = useState("");
    const [newPlayerNickname, setNewPlayerNickname] = useState("");
    const [highlighted, setHighlighted] = useState(false);

    const handleClick = () => {
        if(playerType==="new" && !highlighted){
            setHighlighted(true);
        }
        else if(playerType!="new"){
            handleSelectPlayer(playerNick, playerName);
        }
    }

    const handleCreateNewPlayer = () => {
        setHighlighted(false);
        handleSelectPlayer(newPlayerNickname, newPlayerName);
    }

    return (
        <div className={"playerbannerbody"+(highlighted?" playerbannerhighlighted":"")} onClick={()=>handleClick()}>
            <h3 className={"playernickname"+(highlighted?" playerbannerhighlighted":"")}>{playerNick}</h3>
            <div className="borderdiv"></div>
            {playerType!="new" && playerType!="nameless" && (<a className="playername">Nome: {playerName}</a>)}
            {score && (<ul style={{marginTop:"20px"}}>
                {score.map((item)=>(
                    <li style={{display:"flex", flexDirection:"column", marginBottom:"10px"}}>
                        <a>Jogo: {item.gameName}</a>
                        <a>Vitórias: {item.wins.toString()}</a>
                        <a>Empates: {item.ties.toString()}</a>
                        <a>Derrotas: {item.losses.toString()}</a>
                    </li>
                ))}
            </ul>)}
            {playerType==="new" &&(
                <div>
                    <div style={{position:"relative"}} className={highlighted?"playerbannerhighlighted":"hidden"}>
                        <div style={{marginTop:"10px"}}>
                            <a>Digite o seu nome: </a>
                            <input className="newplayerinput" name="playername" 
                                onChange={(event)=>setNewPlayerName(event.target.value)}
                            />
                        </div>
                        <div style={{marginTop:"10px"}}>
                            <a>Digite o seu apelido: </a>
                            <input className="newplayerinput" name="playername" 
                                onChange={(event)=>setNewPlayerNickname(event.target.value)}
                            />
                        </div>
                        <div style={{marginTop:"100px",display:"flex", "alignItems":"center", "justifyContent":"center"}}>
                            <button className="createnewplayerbutton" onClick={()=>handleCreateNewPlayer()}>Criar</button>
                        </div>
                    </div>
                    <div style={{position:"relative", display:"flex", alignItems:"center", justifyContent:"center"}} className={highlighted?"hidden":""}>
                        <a className="createplayerplus">+</a>
                    </div>
                </div>
            )}
        </div>
    )
}