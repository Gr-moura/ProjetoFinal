import { useState } from "react";
import "./PlayerSelection.css";
import { PlayerBanner } from "../../components/PlayerBanner/PlayerBanner";
import { useNavigate } from "react-router-dom";


export interface playerType{
    playerNick:string;
    playerName:string;
    score?:{
        gameName:string,
        wins:number,
        ties:number,
        losses:number
    }[];
}


export const PlayerSelection = () => {
    const [playerList, setPlayerList] = useState<playerType[]>([]);
    const [playerNumber, setPlayerNumber] = useState(1);
    const [player1, setPlayer1] = useState<playerType>();

    const navigate = useNavigate();

    const handleCreatePlayer = (playerNick:string, playerName:string) => {
        let updatedPlayerList = [...playerList];
        updatedPlayerList.push({
            playerNick:playerNick,
            playerName:playerName,
            score:[
                {
                    gameName:"Jogo da Velha",
                    wins:0,
                    ties:0,
                    losses:0
                },
                {
                    gameName:"Ligue 4",
                    wins:0,
                    ties:0,
                    losses:0,
                },
                {
                    gameName:"Reversi",
                    wins:0,
                    ties:0,
                    losses:0,
                },
                {
                    gameName:"Jogo Extra",
                    wins:0,
                    ties:0,
                    losses:0,
                }
            ]
        });
        setPlayerList(updatedPlayerList);
    }

    const handleSelectPlayer = (playerNick:string, playerName:string) => {
        if(playerNumber===1){
            //selecting player 1
            setPlayer1({
                playerNick:playerNick,
                playerName:playerName
            });
            //removing selected player from the player list  
            let updatedPlayerList = [...playerList];
            updatedPlayerList = updatedPlayerList.filter((player)=>(player.playerName!=playerName && player.playerNick!=playerNick));
            setPlayerList(updatedPlayerList);
            //setting next player to be selected
            setPlayerNumber(2);
        }
        if(playerNumber===2){
            //selecting player 2 and navigating to game selection
            setPlayerNumber(1);
            navigate("/games", {state:{player1:player1, player2:{playerNick:playerNick, playerName:playerName}}});
        }

    }

    return (
        <div className="playerselectionbody">
            <h1 className="screentittle">Selecione o jogador {playerNumber}</h1>
            <div className="playerbannerdisplay">
                <ul style={{display:"flex", flexDirection:"row", paddingBottom:"20px", overflow:"visible"}}>
                    {playerList.map((item)=>(
                        <PlayerBanner
                            playerName={item.playerName}
                            playerNick={item.playerNick}
                            score={item.score}
                            handleSelectPlayer={handleSelectPlayer}
                        />
                    ))}
                    <PlayerBanner 
                        playerName="Novo Jogador" 
                        playerNick="Novo Jogador" 
                        playerType="new"
                        handleSelectPlayer={handleCreatePlayer}
                    />
                    {playerNumber===2 && (<PlayerBanner 
                        playerName="AI" 
                        playerNick="AI" 
                        playerType="nameless"
                        handleSelectPlayer={handleSelectPlayer}
                    />)}
                </ul>
            </div>
        </div>
    );
}